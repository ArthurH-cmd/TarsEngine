#pragma once

#include <TarsEngine/Inc/TarsEngine.h>

class ShapeState : public TarsEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float) override;
	void Render() override;
protected:
	virtual void CreateShape();

	TarsEngine::Graphics::MeshPC mMesh;

	TarsEngine::Graphics::VertexShader mVertexShader;
	TarsEngine::Graphics::MeshBuffer mMeshBuffer;
	TarsEngine::Graphics::PixleShader mPixelShader;

	TarsEngine::Graphics::Camera mCamera;
	TarsEngine::Graphics::ConstantBuffer mConstantBuffer;
};

