#include "Precompiled.h"
#include "SimpleDraw.h"
#include "Camera.h"

#include "ConstantBuffer.h"
#include "VertexTypes.h"
#include "MeshBuffer.h"
#include "PixleShader.h"
#include "VertexShader.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Math;

namespace
{
	class SimpleDrawImpl final
	{
	public:
		void Initilize(uint32_t maxVertexCount);
		void Terminate();

		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);
		void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color);
		void Render(const Camera& camera);

	private:
		VertexShader mVertexShader;
		PixleShader mPixleShader;
		MeshBuffer mMeshBuffer;
		ConstantBuffer mTransformBuffer;

		std::unique_ptr<VertexPC[]> mlineVertices;
		std::unique_ptr<VertexPC[]> mfaceVertices;
		uint32_t mlineVertexCount = 0;
		uint32_t mfaceVertexCount = 0;
		uint32_t mMaxVertexCount = 0;
	};

	void SimpleDrawImpl::Initilize(uint32_t maxVertexCount)
	{
		std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";
		mVertexShader.Initialize<VertexPC>(shaderPath);
		mPixleShader.Initialize(shaderPath);
		mTransformBuffer.Initialize(sizeof(Math::Matrix4));
		mMeshBuffer.Initialize(nullptr,sizeof(VertexPC),maxVertexCount);

		mlineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mfaceVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mlineVertexCount = 0;
		mfaceVertexCount = 0;
		mMaxVertexCount = maxVertexCount;
	}
	void SimpleDrawImpl::Terminate()
	{
		mMeshBuffer.Terminate();
		mTransformBuffer.Terminate();
		mPixleShader.Terminate();
		mVertexShader.Terminate();
	}
	void SimpleDrawImpl::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
	{
		if (mlineVertexCount + 2 <= mMaxVertexCount)
		{
			mlineVertices[mlineVertexCount++] = { v0,color };
			mlineVertices[mlineVertexCount++] = { v1,color };
		}
	}
	void SimpleDrawImpl::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color)
	{
		if (mfaceVertexCount + 3 <= mMaxVertexCount)
		{
			mfaceVertices[mfaceVertexCount++] = { v0,color };
			mfaceVertices[mfaceVertexCount++] = { v1,color };
			mfaceVertices[mfaceVertexCount++] = { v2,color };
		}
	}
	void SimpleDrawImpl::Render(const Camera& camera)
	{
		const Math::Matrix4 matView = camera.GetViewMatrix();
		const Math::Matrix4 matProj = camera.GetProjectionMatrix();
		const Math::Matrix4 wvp = Transpose(matView * matProj);

		mTransformBuffer.Update(&wvp);
		mTransformBuffer.BindVS(0);

		mVertexShader.Bind();
		mPixleShader.Bind();

		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Update(mlineVertices.get(), mlineVertexCount);
		mMeshBuffer.Render();

		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
		mMeshBuffer.Update(mfaceVertices.get(), mfaceVertexCount);
		mMeshBuffer.Render();

		mlineVertexCount = 0;
		mfaceVertexCount = 0;
	}

	std::unique_ptr<SimpleDrawImpl> sSimpleDrawInstance;
}

void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
	sSimpleDrawInstance = std::make_unique<SimpleDrawImpl>();
	sSimpleDrawInstance->Initilize(maxVertexCount);
}
void SimpleDraw::StaticTerminate()
{
    if (sSimpleDrawInstance != nullptr)
    {
        sSimpleDrawInstance->Terminate();
		sSimpleDrawInstance.reset();
    }
	
}
void SimpleDraw::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
{
	sSimpleDrawInstance->AddLine(v0, v1, color);
}
void SimpleDraw::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color)
{
	sSimpleDrawInstance->AddFace(v0, v1, v2, color);
}
void SimpleDraw::AddAABB(const Vector3& min, const Vector3& max, const Color& color)
{
    AddAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}
void SimpleDraw::AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color)
{
    const Vector3 trf = { maxX, maxY, minZ };
    const Vector3 brf = { maxX, minY, minZ };
    const Vector3 tlf = { minX, maxY, minZ };
    const Vector3 blf = { minX, minY, minZ };

    const Vector3 trb = { maxX, maxY, maxZ };
    const Vector3 brb = { maxX, minY, maxZ };
    const Vector3 tlb = { minX, maxY, maxZ };
    const Vector3 blb = { minX, minY, maxZ };

    // front
    AddLine(trf, brf, color);
    AddLine(brf, blf, color);
    AddLine(blf, tlf, color);
    AddLine(tlf, trf, color);

    // back
    AddLine(trb, brb, color);
    AddLine(brb, blb, color);
    AddLine(blb, tlb, color);
    AddLine(tlb, trb, color);

    // top
    AddLine(trb, trf, color);
    AddLine(tlb, tlf, color);

    // bottom
    AddLine(brb, brf, color);
    AddLine(blb, blf, color);
}
void SimpleDraw::AddFilledAABB(const Vector3& min, const Vector3& max, const Color& color)
{
    AddFilledAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}
void SimpleDraw::AddFilledAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color)
{
    const Vector3 trf = { maxX, maxY, minZ };
    const Vector3 brf = { maxX, minY, minZ };
    const Vector3 tlf = { minX, maxY, minZ };
    const Vector3 blf = { minX, minY, minZ };

    const Vector3 trb = { maxX, maxY, maxZ };
    const Vector3 brb = { maxX, minY, maxZ };
    const Vector3 tlb = { minX, maxY, maxZ };
    const Vector3 blb = { minX, minY, maxZ };

    // front
    AddFace(trf, brf, blf, color);
    AddFace(trf, blf, tlf, color);

    // back
    AddFace(trb, tlb, blb, color);
    AddFace(trb, blb, brb, color);

    // top
    AddFace(trb, trf, tlf, color);
    AddFace(trb, tlf, tlb, color);

    // bottom
    AddFace(brb, blf, brf, color);
    AddFace(brb, blb, blf, color);

    // right
    AddFace(trb, brb, brf, color);
    AddFace(trb, brf, trf, color);

    // left
    AddFace(tlb, blf, blb, color);
    AddFace(tlb, tlf, blf, color);
}
void SimpleDraw::AddSphere(uint32_t slices, uint32_t rings, float radius, const Math::Vector3& origin, const Color& color)
{
    Vector3 v0 = Vector3::Zero;
    Vector3 v1 = Vector3::Zero;

    const float vertRotation = (Constants::TwoPi / static_cast<float>(rings - 1));
    const float horzRotation = (Constants::TwoPi / static_cast<float>(slices - 1));
    for (uint32_t r = 0; r < rings; ++r)
    {
        float rPos0 = static_cast<float>(r);
        float rPos1 = static_cast<float>(r + 1);
        float phi0 = rPos0 * vertRotation;
        float phi1 = rPos1 * vertRotation;
        for (uint32_t s = 0; s < slices; ++s)
        {
            float sPos0 = static_cast<float>(s);
            float sPos1 = static_cast<float>(s + 1);
            float rot0 = sPos0 * horzRotation;
            float rot1 = sPos1 * horzRotation;

            v0 = {
                radius * sin(rot0) * sin(phi0),
                radius * cos(phi0),
                radius * cos(rot0) * sin(phi0)
            };

            v1 = {
                radius * sin(rot1) * sin(phi0),
                radius * cos(phi0),
                radius * cos(rot1) * sin(phi0)
            };

            AddLine(v0 + origin, v1 + origin, color);

            v1 = {
                radius * sin(rot0) * sin(phi1),
                radius * cos(phi1),
                radius * cos(rot0) * sin(phi1)
            };
            AddLine(v0 + origin, v1 + origin, color);
        }
    }
}
void SimpleDraw::AddGroundPlane(float size, const Color& color)
{
    const float hs = size * 0.5f;
    const uint32_t iSize = static_cast<uint32_t>(size);
    for (uint32_t i = 0; i <= iSize; ++i)
    {
        AddLine({ i - hs, 0.0f, -hs }, { i - hs, 0.0f, hs }, color);
        AddLine({ -hs, 0.0f, i - hs }, { hs, 0.0f, i - hs }, color);
    }
}
void SimpleDraw::AddGroundCircle(uint32_t slices, float radius, const Math::Vector3& origin, const Color& color)
{
    Vector3 v0 = Vector3::Zero;
    Vector3 v1 = Vector3::Zero;
    float horzRotation = (Constants::TwoPi / static_cast<float>(slices - 1));
    for (uint32_t s = 0; s < slices; ++s)
    {
        float sPos0 = static_cast<float>(s);
        float sPos1 = static_cast<float>(s + 1);
        float rot0 = sPos0 * horzRotation;
        float rot1 = sPos1 * horzRotation;

        v0 = {
            radius * sin(rot0),
            0.0f,
            radius * cos(rot0)
        };
        v1 = {
            radius * sin(rot1),
            0.0f,
            radius * cos(rot1)
        };
        AddLine(v0, v1, color);
    }
}
void SimpleDraw::AddTransform(const Matrix4& matrix)
{
    const Vector3 side = { matrix._11, matrix._12, matrix._13 };
    const Vector3 up = { matrix._21, matrix._22, matrix._23 };
    const Vector3 fwd = { matrix._31, matrix._32, matrix._33 };
    const Vector3 pos = { matrix._41, matrix._42, matrix._43 };

    AddLine(pos, pos + side, Colors::Red);
    AddLine(pos, pos + up, Colors::Green);
    AddLine(pos, pos + fwd, Colors::Blue);
}
void SimpleDraw::Render(const Camera& camera)
{
	sSimpleDrawInstance->Render(camera);
}