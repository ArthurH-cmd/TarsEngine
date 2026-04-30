#include "ShapeStates.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;

void ShapeState::Initialize()
{
	CreateShape();

	auto device = GraphicsSystem::Get()->GetDevice();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = mVertices.data();
	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "Failed to create mesh buffer.");

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";
}

void ShapeState::Terminate()
{

}

void ShapeState::Update(float deltatime)
{

}

void ShapeState::Render() 
{

}

void ShapeState::CreateShape()
{
	mVertices.push_back({ {-0.5f,-0.5f,0.0f} });
	mVertices.push_back({ {0.0f,0.5f,0.0f} });
	mVertices.push_back({ {0.5f,-0.5f,0.0f} });
}