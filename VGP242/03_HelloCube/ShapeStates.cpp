#include "ShapeStates.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Input;

void ShapeState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    // Create shape
    CreateShapes();
    mMeshBuffer.Initialize(mVertices.data(), sizeof(VertexPC), mVertices.size());

    std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";
    mVertexShader.Initialize<VertexPC>(shaderPath);
    mPixelShader.Initialize(shaderPath);
    mConstantBuffer.Initialize(sizeof(Math::Matrix4));
}

void ShapeState::Terminate()
{
    mVertices.clear();
    mConstantBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mMeshBuffer.Terminate();
}

void ShapeState::Update(float deltaTime)
{
    InputSystem* input = InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
        mCamera.Walk(moveSpeed * deltaTime);
    if (input->IsKeyDown(KeyCode::S))
        mCamera.Walk(-moveSpeed * deltaTime);
    if (input->IsKeyDown(KeyCode::A))
        mCamera.Strafe(-moveSpeed * deltaTime);
    if (input->IsKeyDown(KeyCode::D))
        mCamera.Strafe(moveSpeed * deltaTime);
    if (input->IsKeyDown(KeyCode::E))
        mCamera.Rise(moveSpeed * deltaTime);
    if (input->IsKeyDown(KeyCode::Q))
        mCamera.Rise(-moveSpeed * deltaTime);
    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }
}

void ShapeState::Render()
{
    // Prepare the GPU
    mVertexShader.Bind();
    mPixelShader.Bind();

    // Sync buffer information
    mConstantBuffer.BindVS(0);

    // Update buffer data
    Math::Matrix4 matWorld = Math::Matrix4::Identity;
    Math::Matrix4 matView = mCamera.GetViewMatrix();
    Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
    Math::Matrix4 wvp = matWorld * matView * matProj;
    wvp = Math::Transpose(wvp);
    mConstantBuffer.Update(&wvp);

    // Render object
    mMeshBuffer.Render();
}

void ShapeState::CreateShapes()
{
    // Front
    mVertices.push_back({ {-0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ { 0.5f,  0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Green} });
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Blue} });

    mVertices.push_back({ {-0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Red} });
    mVertices.push_back({ {-0.5f,  0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Yellow} });
    mVertices.push_back({ { 0.5f,  0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Green} });

    // Back
    mVertices.push_back({ { 0.5f, -0.5f, 0.5f}, {TarsEngine::Graphics::Colors::Cyan} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.5f}, {TarsEngine::Graphics::Colors::Magenta} });
    mVertices.push_back({ {-0.5f, -0.5f, 0.5f}, {TarsEngine::Graphics::Colors::Orange} });

    mVertices.push_back({ {-0.5f, -0.5f, 0.5f}, {TarsEngine::Graphics::Colors::Orange} });
    mVertices.push_back({ { 0.5f,  0.5f, 0.5f}, {TarsEngine::Graphics::Colors::Magenta} });
    mVertices.push_back({ {-0.5f,  0.5f, 0.5f}, {TarsEngine::Graphics::Colors::White} });

    // Right
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Blue} });
    mVertices.push_back({ { 0.5f,  0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Magenta} });
    mVertices.push_back({ { 0.5f, -0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Cyan} });

    mVertices.push_back({ { 0.5f,  0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Green} });
    mVertices.push_back({ { 0.5f,  0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Magenta} });
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Blue} });

    // Left
    mVertices.push_back({ {-0.5f, -0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Orange} });
    mVertices.push_back({ {-0.5f,  0.5f,  0.5f}, {TarsEngine::Graphics::Colors::White} });
    mVertices.push_back({ {-0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Red} });

    mVertices.push_back({ {-0.5f,  0.5f,  0.5f}, {TarsEngine::Graphics::Colors::White} });
    mVertices.push_back({ {-0.5f,  0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Yellow} });
    mVertices.push_back({ {-0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Red} });

    // Top
    mVertices.push_back({ {-0.5f, 0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Yellow} });
    mVertices.push_back({ { 0.5f, 0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Magenta} });
    mVertices.push_back({ { 0.5f, 0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Green} });

    mVertices.push_back({ {-0.5f, 0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Yellow} });
    mVertices.push_back({ {-0.5f, 0.5f,  0.5f}, {TarsEngine::Graphics::Colors::White} });
    mVertices.push_back({ { 0.5f, 0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Magenta} });

    // Bottom
    mVertices.push_back({ {-0.5f, -0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Orange} });
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Blue} });
    mVertices.push_back({ { 0.5f, -0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Cyan} });

    mVertices.push_back({ { 0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Blue} });
    mVertices.push_back({ {-0.5f, -0.5f,  0.5f}, {TarsEngine::Graphics::Colors::Orange} });
    mVertices.push_back({ {-0.5f, -0.5f, -0.5f}, {TarsEngine::Graphics::Colors::Red} });
}
