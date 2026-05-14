#include "ShapeStates.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Input;

void ShapeState::Initialize()
{
	CreateShape();
	mMeshBuffer.Initialize(mVertices.data(),sizeof(VertexPC),mVertices.size());

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoColor.fx";
	mVertexShader.Initialize<VertexPC>(shaderPath);
	mPixelShader.Initialize(shaderPath);
}

void ShapeState::Terminate()
{
	mVertices.clear();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void ShapeState::Update(float deltatime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("QuadState");
	}
}

void ShapeState::Render() 
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mMeshBuffer.Render();
}

void ShapeState::CreateShape()
{
	
	mVertices.push_back({ {-0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::AliceBlue} });
	mVertices.push_back({ {0.0f,0.5f,0.0f}, {TarsEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ {0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::Green} });
}

void QuadState::Update(float deltaTime)
{

	if(InputSystem::Get()->IsKeyPressed(KeyCode::UP))
	{
		MainApp().ChangeState("ShapeState");
	}
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("HouseState");
	}
}

void HouseState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("QuadState");
	}
}

void QuadState::CreateShape()
{
	mVertices.push_back({ {-0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::AliceBlue} });
	mVertices.push_back({ {-0.5f,0.5f,0.0f}, {TarsEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ {0.5f,0.5f,0.0f},{TarsEngine::Graphics::Colors::Green} });

	mVertices.push_back({ {-0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::AliceBlue} });
	mVertices.push_back({ {0.5f,0.5f,0.0f}, {TarsEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ {0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::Green} });
}



void HouseState::CreateShape()
{
	mVertices.push_back({ {-0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::AliceBlue} });
	mVertices.push_back({ {-0.5f,0.5f,0.0f}, {TarsEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ {0.5f,0.5f,0.0f},{TarsEngine::Graphics::Colors::Green} });

	mVertices.push_back({ {-0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::AliceBlue} });
	mVertices.push_back({ {0.5f,0.5f,0.0f}, {TarsEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ {0.5f,-0.5f,0.0f},{TarsEngine::Graphics::Colors::Green} });

	mVertices.push_back({ {-0.5f, 0.5f, 0.0f },{ TarsEngine::Graphics::Colors::AliceBlue } });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f },{ TarsEngine::Graphics::Colors::Blue } });
	mVertices.push_back({ { 0.0f, 1.0f, 0.0f },{ TarsEngine::Graphics::Colors::Green } });
}

