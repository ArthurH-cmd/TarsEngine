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

	struct Vertex
	{
		TarsEngine::Math::Vector3 position;
		TarsEngine::Graphics::Color color;
	};

	using Vertices = std::vector<TarsEngine::Graphics::VertexPC>;
	Vertices mVertices;


	TarsEngine::Graphics::VertexShader mVertexShader;
	TarsEngine::Graphics::MeshBuffer mMeshBuffer;
	TarsEngine::Graphics::PixleShader mPixelShader;
};

class QuadState : public ShapeState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class HouseState : public ShapeState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

