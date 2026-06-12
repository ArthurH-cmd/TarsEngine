#include "GameState.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}

void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
    UpdateCamera(deltaTime);
}

enum class Shape
{
    None,
    AABB,
    AABBFilled,
    Sphere,
    GroundPlane,
    GroundCircle,
    Transform
};

const char* gShapeNames[] =
{
    "None",
    "AABB",
    "AABBFilled",
    "Sphere",
    "GroundPlane",
    "GroundCircle",
    "Transform"
};

Shape gCurrentShape = Shape::None;
Color gShapeColor = Colors::White;
float gPlaneSize = 10.0f;

void GameState::Render()
{
    switch (gCurrentShape)
    {
    case Shape::None: break;
    case Shape::AABB:
        SimpleDraw::AddAABB({ 0.0f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f }, gShapeColor);
        break;
    case Shape::AABBFilled:
        SimpleDraw::AddFilledAABB({ 0.0f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f }, gShapeColor);
        break;
    case Shape::Sphere:
        SimpleDraw::AddSphere(32, 16, 1.0f, { 0.0f, 0.5f, 0.0f }, gShapeColor);
        break;
    case Shape::GroundPlane:
        SimpleDraw::AddGroundPlane(gPlaneSize, gShapeColor);
        break;
    case Shape::GroundCircle:
        SimpleDraw::AddGroundCircle(32, gPlaneSize * 0.5f, { 0.0f, 0.0f, 0.0f }, gShapeColor);
        break;
    case Shape::Transform:
        SimpleDraw::AddTransform(Math::Matrix4::Translation({ 0.0f, 0.0f, 0.0f }));
        break;
    default:
        break;
    }

    SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::ColorEdit4("ShapeColor", &gShapeColor.r);
    int currentShape = (int)gCurrentShape;
    if (ImGui::Combo("Shape", &currentShape, gShapeNames, std::size(gShapeNames)))
    {
        gCurrentShape = (Shape)currentShape;
    }

    ImGui::DragFloat("PlaneSize", &gPlaneSize, 1.0f, 1.0f, 10000.0f);
    ImGui::End();
}

void GameState::UpdateCamera(float deltaTime)
{
    InputSystem* input = InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Rise(-moveSpeed * deltaTime);
    }

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }
}