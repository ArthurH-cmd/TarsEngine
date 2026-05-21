#include "ShapeStates.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Input;

void ShapeState::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-5.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	CreateShape();
	mMeshBuffer.Initialize(mMesh);

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";
	mVertexShader.Initialize<VertexPC>(shaderPath);
	mPixelShader.Initialize(shaderPath);
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
}

void ShapeState::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void ShapeState::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 20.0f : 10.0f;
	const float turnSpeed = 0.5f;

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
	// prepare the gpu
	mVertexShader.Bind();
	mPixelShader.Bind();

	mConstantBuffer.BindVS(0);

	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	Math::Matrix4 wvp = matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	
	mMeshBuffer.Render();
}

void ShapeState::CreateShape()
{
	//mMesh = MeshBuilder::CreateVertexCubePC(1, Colors::White);
	//mMesh = MeshBuilder::CreateCubePC(1);
	//mMesh = MeshBuilder::CreateBoxPC(3.0f,4.0f,2.0f);
	//mMesh = MeshBuilder::CreatePyramidPC(1.0f);
	//mMesh = MeshBuilder::CreatePlanePC(10, 10, 1.0f,false);
	//mMesh = MeshBuilder::CreateCylinderPC(10, 10);
	mMesh = MeshBuilder::CreateSpherePC(30, 30, 1.0f);
}

