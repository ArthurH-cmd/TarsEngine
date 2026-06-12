#include "ShapeStates.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Input;

void ShapeState::Initialize()
{
    CreateShapes();
    mMeshBuffer.Initialize(mVertices.data(), sizeof(VertexPC), mVertices.size());

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

void ShapeState::Update(float deltaTime)
{
    if (InputSystem::Get()->IsKeyPressed(KeyCode::UP))
    {
        MainApp().ChangeState("HouseState");
    }
}

void ShapeState::Render()
{
    mVertexShader.Bind();
    mPixelShader.Bind();
    mMeshBuffer.Render();
}

void ShapeState::CreateShapes()
{
    mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
}

void QuadState::Update(float deltaTime)
{
    if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
    {
        MainApp().ChangeState("LogoState");
    }
}

void QuadState::CreateShapes()
{
    mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {-0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {0.5f,   0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });

    mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {0.5f,   0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {0.5f,  -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
}

void HouseState::Update(float deltaTime)
{
    if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
    {
        MainApp().ChangeState("QuadState");
    }
}

void HouseState::CreateShapes()
{
    // First Triangle
    mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {-0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });

    // Second Triangle
    mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });

    // Third Triangle
    mVertices.push_back({ {-0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.0f,  1.0f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
}

void LogoState::Update(float deltaTime)
{
    if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
    {
        MainApp().ChangeState("ShapeState");
    }
}

void LogoState::CreateShapes()
{
    // First Triangle
    mVertices.push_back({ {0.0f, 0.0f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });

    // Second Triangle
    mVertices.push_back({ {0.0f, 0.0f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {-0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });

    // Third Triangle
    mVertices.push_back({ {0.0f, 0.0f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f, -0.5f, 0.0f}, {TarsEngine::Graphics::Colors::Red} });
}
