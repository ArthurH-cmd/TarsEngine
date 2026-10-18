#include "GameState.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.4f, 0.4f, 0.4f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.5f, 0.5f, 0.5f, 1.0f };

	// OBJ1
	Mesh ball1 = MeshBuilder::CreateSphere(150, 150, 2.0f);
	mRenderObject.transform.position = { -3.0f, 0.5f, 0.5f };
	mRenderObject.meshBuffer.Initialize(ball1);

	//OBJ2
	Mesh ball2 = MeshBuilder::CreateSphere(50, 50, 2.0f);
	mRenderObject2.transform.position = { 3.0f, 0.5f, 0.5f };
	mRenderObject2.meshBuffer.Initialize(ball2);
	

	TextureManager* tm = TextureManager::Get();

	//OBJ1 TEXTURE
	mRenderObject.diffuseMapId = tm->LoadTexture("wood_diffuse.jpg");
	mRenderObject.specMapId = tm->LoadTexture("wood_specular.jpg");
	mRenderObject.normMapId = tm->LoadTexture("wood_normal.jpg");
	mRenderObject.bumpMapId = tm->LoadTexture("wood_bump.jpg");

	//OBJ2 TEXTURE
	mRenderObject2.diffuseMapId = tm->LoadTexture("brick_diffuse.jpg");
	mRenderObject2.normMapId = tm->LoadTexture("brick_normal.jpg");
	mRenderObject2.bumpMapId = tm->LoadTexture("brick_bump.jpg");
	mRenderObject2.specMapId = tm->LoadTexture("brick_specular.jpg");

	std::filesystem::path shaderpath = L"../../Assets/Shaders/Standerd.fx";
	mStandardEffect.Initialize(shaderpath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	shaderpath = L"../../Assets/Shaders/CelShader.fx";
	mStandardEffectCel.Initialize(shaderpath);
	mStandardEffectCel.SetCamera(mCamera);
	mStandardEffectCel.SetDirectionalLight(mDirectionalLight);
}
void GameState::Terminate()
{
	mStandardEffect.Terminate();
	mRenderObject.Terminate();
	mRenderObject2.Terminate();
	mStandardEffectCel.Terminate();
}
void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}
void GameState::Render()
{
	SimpleDraw::AddGroundPlane(30.0f, Colors::Aqua);
	SimpleDraw::Render(mCamera);

	if (mUseCellShading)
	{
		mStandardEffectCel.Begin();
			mStandardEffectCel.Render(mRenderObject);
			mStandardEffectCel.Render(mRenderObject2);
		mStandardEffectCel.End();
	}
	else
	{
		mStandardEffect.Begin();
			mStandardEffect.Render(mRenderObject);
			mStandardEffect.Render(mRenderObject2);
		mStandardEffect.End();
	}
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if(ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Light Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient#Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse#Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular#Light", &mDirectionalLight.specular.r);
	}
	
	if(ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Emmisive##Material", &mRenderObject.material.emissive.r);
		ImGui::ColorEdit4("Ambient##Material", &mRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Material", &mRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##Material", &mRenderObject.material.specular.r);
		ImGui::DragFloat("Shininess##Material", &mRenderObject.material.shininess, 0.1f, 0.0f, 100.0f);
	}

	ImGui::Checkbox("Use Cell Shading", &mUseCellShading);
	if (mUseCellShading)
	{
		mStandardEffectCel.DebugUI();
	}
	else
	{
		mStandardEffect.DebugUI();
	}

	ImGui::End();
}
void GameState::UpdateCamera(float deltaTime)
{
	InputSystem* input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 5.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (input->IsKeyDown(KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (input->IsKeyDown(KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (input->IsKeyDown(KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
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