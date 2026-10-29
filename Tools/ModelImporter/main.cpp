#include <TarsEngine/Inc/TarsEngine.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <cstdio>

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Math;

struct Arguments
{
	std::filesystem::path inputFileName;
	std::filesystem::path outputFileName;
	float scale = 1.0f;
};

std::optional<Arguments> ParseArgs(int argc, char* argv[])
{
	if (argc < 1)
	{
		return std::nullopt;
	}
	Arguments args;
	args.inputFileName = argv[argc - 2];
	args.outputFileName = argv[argc - 1];
	for (int i = 0; i + 2 < argc; ++i)
	{
		if(strcmp(argv[i], "-scale") == 0)
		{
			args.scale = atof(argv[i + 1]);
			++i;
		}
	}
	return args;
}

Vector3 toVector3(const aiVector3D& v)
{ 
	return{
		static_cast<float>(v.x),
		static_cast<float>(v.y),
		static_cast<float>(v.z)
	};
}
Vector2 toTextCoord(const aiVector3D& v)
{
	return{
		static_cast<float>(v.x),
		static_cast<float>(v.y),
	};
}
Color toColor(const aiColor3D& c)
{
	return {
		static_cast<float>(c.r),
		static_cast<float>(c.g),
		static_cast<float>(c.b),
		1.0f
	};
}

void ExportEmbeddedTexture(const aiTexture* texture, const Arguments& args, const std::filesystem::path& filename)
{
	printf("Extracting embedded textures %s\n", filename.u8string().c_str());

	std::string fullFileName = args.outputFileName.u8string();
	fullFileName = fullFileName.substr(0, fullFileName.rfind('/') + 1);
	fullFileName += filename.filename().u8string();

	FILE* file = nullptr;
	auto err = fopen_s(&file, fullFileName.c_str(), "wb");
	if (err != 0 || file == nullptr)
	{
		printf("error: failed to open file %s for saving\n", fullFileName.c_str());
		return;
	}

	std::size_t written = fwrite(texture->pcData, 1, texture->mWidth, file);
	ASSERT(written == texture->mWidth, "error: failed to extract embedded textures");
	fclose(file);
}

std::string FindTexture(const aiScene* scene, const aiMaterial* aiMaterial,
	aiTextureType textureType, const Arguments& args, const std::string& suffix,
	uint32_t materialIndex)
{
	const uint32_t textureCount = aiMaterial->GetTextureCount(textureType);
	if (textureCount == 0)
	{
		return "";
	}

	std::filesystem::path textureName;
	aiString texturePath;
	if (aiMaterial->GetTexture(textureType,0,&texturePath) == aiReturn_SUCCESS)
	{
		if (texturePath.C_Str()[0] == '*')
		{
			std::string fileName = args.inputFileName.u8string();
			fileName.erase(fileName.length() - 4);
			fileName += suffix;
			fileName += texturePath.C_Str()[1];

			ASSERT(scene->HasTextures(), "ERROR: no embedded textures found");

			int textureIndex = atoi(texturePath.C_Str() + 1);
			ASSERT(textureIndex < scene->mNumTextures,"error invalid Texture index");

			const aiTexture* embeddedTexture = scene->mTextures[textureIndex];
			ASSERT(embeddedTexture->mHeight == 0, "Error: uncompressed texture found");

			if (embeddedTexture->CheckFormat("jpg"))
			{
				fileName += ".jpg";
			}
			else if (embeddedTexture->CheckFormat("png"))
			{
				fileName += ".png";
			}
			else
			{
				ASSERT(false, "Error: unsupported texture format");
			}

			printf("Adding texture %s\n", fileName.c_str());
			ExportEmbeddedTexture(embeddedTexture, args, fileName);
			textureName = fileName;
		}
		else if (auto embeddedTexture = scene->GetEmbeddedTexture(texturePath.C_Str()); embeddedTexture != nullptr)
		{
			std::filesystem::path embeddedFilePath = texturePath.C_Str();
			std::string filename = args.inputFileName.u8string();
			filename.erase(filename.length() - 4);
			filename += suffix;
			filename += "_" + std::to_string(materialIndex);
			filename += embeddedFilePath.extension().u8string();

			printf("Adding texture %s\n", filename.c_str());
			ExportEmbeddedTexture(embeddedTexture, args, filename);
			textureName = filename;
		}
		else
		{
			std::filesystem::path filePath = texturePath.C_Str();
			std::string fileName = filePath.u8string();

			printf("Adding Textures %s\n", fileName.c_str());
			textureName = fileName;
		}
	}

	return textureName.filename().u8string();
}



// <scale> <scaleValue> <inputfilename> <outputfilename> 
int main(int argc, char* argv[])
{
	const auto argsOpt = ParseArgs(argc, argv);
	if (!argsOpt.has_value())
	{
		printf("not enough arguments, import fbx failed");
		return -1;
	}

	printf("Begin Import\n");
	const Arguments& args = argsOpt.value();

	Assimp::Importer importer;
	importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
	const uint32_t flags = aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded;
	const aiScene* scene = importer.ReadFile(args.inputFileName.u8string().c_str(), flags);

	if (scene == nullptr)
	{
		printf("ERROR %s\n", importer.GetErrorString());
		return -1;
	}
	printf("Importing %s...\n", args.inputFileName.u8string().c_str());

	Model model;
	if (scene->HasMeshes())
	{
		printf("Reading Mesh Data...\n");
		for (uint32_t meshIndex = 0; meshIndex < scene-> mNumMeshes; ++meshIndex)
		{
			const auto& aiMesh = scene->mMeshes[meshIndex];
			if (aiMesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			{
				continue;
			}

			const uint32_t numVertices = aiMesh->mNumVertices;
			const uint32_t numFaces = aiMesh->mNumFaces;
			const uint32_t numIndices = aiMesh->mNumFaces * 3;

			Model::MeshData& meshData = model.meshData.emplace_back();

			printf("Reading Material Index...\n");
			meshData.materialIndex = aiMesh->mMaterialIndex;

			printf("Reading Vertices...\n");
			Mesh& mesh = meshData.mesh;
			mesh.vertices.reserve(numVertices);

			const aiVector3D* positions = aiMesh->mVertices;
			const aiVector3D* normals = aiMesh->mNormals;
			const aiVector3D* tangents = (aiMesh->HasTangentsAndBitangents()) ? aiMesh->mTangents : nullptr;
			const aiVector3D* texCoords = (aiMesh->HasTextureCoords(0)) ? aiMesh->mTextureCoords[0] : nullptr;
			for (uint32_t v = 0; v < numVertices; ++v)
			{
				Vertex& vertex = mesh.vertices.emplace_back();
				vertex.position = toVector3(positions[v]) * args.scale;
				vertex.normal = toVector3(normals[v]);
				vertex.tangent = tangents ? toVector3(tangents[v]) : Vector3::Zero;
				vertex.uvCoord = texCoords ? toTextCoord(texCoords[v]) : Vector2::Zero;
			}

			printf("Reading Indices...\n");
			mesh.indices.reserve(numIndices);
			const auto& aiFaces = aiMesh->mFaces;
			for (uint32_t f = 0; f < numFaces; ++f)
			{
				const auto& aiFace = aiFaces[f];
				for (uint32_t i = 0; i < 3; ++i)
				{
					mesh.indices.push_back(aiFace.mIndices[i]);
				}
			}
		}
	}

	if (scene->HasMaterials())
	{
		printf("reading mat Data...\n");

		const uint32_t numMaterials = scene->mNumMaterials;
		model.materialData.reserve(numMaterials);
		for (uint32_t materialIndex = 0; materialIndex < numMaterials; ++ materialIndex)
		{
			const auto& aiMaterial = scene->mMaterials[materialIndex];
			aiColor3D emissive, ambient, diffuse, specular;
			ai_real specularPower = 10.0f;

			aiMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
			aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specular);

			Model::MaterialData& materialData = model.materialData.emplace_back();
			materialData.material.emissive = toColor(emissive);
			materialData.material.ambient = toColor(ambient);
			materialData.material.diffuse = toColor(diffuse);
			materialData.material.specular = toColor(specular);

			materialData.diffuseName = FindTexture(scene, aiMaterial, aiTextureType_DIFFUSE, args, "_diff", materialIndex);
			materialData.normName = FindTexture(scene, aiMaterial, aiTextureType_NORMALS, args, "_norm", materialIndex);
			materialData.specName = FindTexture(scene, aiMaterial, aiTextureType_SPECULAR, args, "_spec", materialIndex);
			materialData.bumpName = FindTexture(scene, aiMaterial, aiTextureType_DISPLACEMENT, args, "_bump", materialIndex);
		}
	}


	// save the data
	printf("Saving Model...\n");
	ModelIO::SaveModel(args.outputFileName, model);

	printf("Saving Material...\n");
	ModelIO::SaveMaterial(args.outputFileName, model);

	printf("Import Complete :)\n");

	return 0;
}