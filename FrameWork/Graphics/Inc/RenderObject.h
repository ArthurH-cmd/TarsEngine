#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "Material.h"
#include "TextureManager.h"
#include "ModelManager.h"

namespace TarsEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();

		MeshBuffer meshBuffer; // shape
		Transform transform; // position, rotation, scale
		Material material;  // light data
		TextureId diffuseMapId; // diffuse texture (color)
		TextureId specMapId; // specular texture (reflectivity)
		TextureId normMapId; // normal texture 
		TextureId bumpMapId; // bump texture (height map)
	};

	class RenderGroup
	{
	public:
		void Initialize(const std::filesystem::path& modelFilePath);
		void Initialize(const Model& model);
		void Terminate();

		ModelId modelId;
		Transform transform;
		std::vector<RenderObject> renderObjects;
	};
}
