#include "GameState.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;
using namespace TarsEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// Sky sphere
	Graphics::MeshPX skySphere = MeshBuilder::CreateSkySpherePX(30, 30, 100.0f);
	mSkyMeshBuf.Initialize(skySphere);

	// Sun
	Graphics::MeshPX sun = MeshBuilder::CreateSpherePX(30, 30, 0.7f);
	mSunMeshBuf.Initialize(sun);

	// Mercury
	Graphics::MeshPX mercury = MeshBuilder::CreateSpherePX(30, 30, 0.15f);
	mMercuryMeshBuf.Initialize(mercury);
	mMercuryOrbitDistance = 1.8f;

	// Venus
	Graphics::MeshPX venus = MeshBuilder::CreateSpherePX(30, 30, 0.22f);
	mVenusMeshBuf.Initialize(venus);
	mVenusOrbitDistance = 2.6f;

	// Earth
	Graphics::MeshPX earth = MeshBuilder::CreateSpherePX(30, 30, 0.25f);
	mEarthMeshBuf.Initialize(earth);
	mEarthOrbitDistance = 3.5f;

	// Moon
	Graphics::MeshPX moon = MeshBuilder::CreateSpherePX(30, 30, 0.05f);
	mMoonMeshBuf.Initialize(moon);
	mMoonOrbitDistance = 0.5f;

	// Mars
	Graphics::MeshPX mars = MeshBuilder::CreateSpherePX(30, 30, 0.18f);
	mMarsMeshBuf.Initialize(mars);
	mMarsOrbitDistance = 4.5f;

	// Jupiter
	Graphics::MeshPX jupiter = MeshBuilder::CreateSpherePX(30, 30, 0.5f);
	mJupiterMeshBuf.Initialize(jupiter);
	mJupiterOrbitDistance = 6.0f;

	// Saturn
	Graphics::MeshPX saturn = MeshBuilder::CreateSpherePX(30, 30, 0.42f);
	mSaturnMeshBuf.Initialize(saturn);
	mSaturnOrbitDistance = 7.8f;

	// Uranus
	Graphics::MeshPX uranus = MeshBuilder::CreateSpherePX(30, 30, 0.32f);
	mUranusMeshBuf.Initialize(uranus);
	mUranusOrbitDistance = 9.5f;

	// Neptune
	Graphics::MeshPX neptune = MeshBuilder::CreateSpherePX(30, 30, 0.30f);
	mNeptuneMeshBuf.Initialize(neptune);
	mNeptuneOrbitDistance = 11.0f;

	// Pluto
	Graphics::MeshPX pluto = MeshBuilder::CreateSpherePX(30, 30, 0.1f);
	mPlutoMeshBuf.Initialize(pluto);
	mPlutoOrbitDistance = 12.5f;

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderPath);
	mPixelShader.Initialize(shaderPath);
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	mSkyTextureId = TextureManager::Get()->LoadTexture("space.jpg");
	mSunTextureId = TextureManager::Get()->LoadTexture("planets/sun.jpg");
	mMercuryTextureId = TextureManager::Get()->LoadTexture("planets/mercury.jpg");
	mVenusTextureId = TextureManager::Get()->LoadTexture("planets/venus.jpg");
	mEarthTextureId = TextureManager::Get()->LoadTexture("earth.jpg");
	mMoonTextureId = TextureManager::Get()->LoadTexture("planets/mercury.jpg");
	mMarsTextureId = TextureManager::Get()->LoadTexture("planets/mars.jpg");
	mJupiterTextureId = TextureManager::Get()->LoadTexture("planets/jupiter.jpg");
	mSaturnTextureId = TextureManager::Get()->LoadTexture("planets/saturn.jpg");
	mUranusTextureId = TextureManager::Get()->LoadTexture("planets/uranus.jpg");
	mNeptuneTextureId = TextureManager::Get()->LoadTexture("planets/neptune.jpg");
	mPlutoTextureId = TextureManager::Get()->LoadTexture("planets/pluto.jpg");
	mBasketballTextureId = TextureManager::Get()->LoadTexture("misc/basketball.jpg");
}

void GameState::Terminate()
{
	TextureManager::Get()->ReleaseTexture(mBasketballTextureId);
	TextureManager::Get()->ReleaseTexture(mPlutoTextureId);
	TextureManager::Get()->ReleaseTexture(mNeptuneTextureId);
	TextureManager::Get()->ReleaseTexture(mUranusTextureId);
	TextureManager::Get()->ReleaseTexture(mSaturnTextureId);
	TextureManager::Get()->ReleaseTexture(mJupiterTextureId);
	TextureManager::Get()->ReleaseTexture(mMarsTextureId);
	TextureManager::Get()->ReleaseTexture(mMoonTextureId);
	TextureManager::Get()->ReleaseTexture(mEarthTextureId);
	TextureManager::Get()->ReleaseTexture(mVenusTextureId);
	TextureManager::Get()->ReleaseTexture(mMercuryTextureId);
	TextureManager::Get()->ReleaseTexture(mSunTextureId);
	TextureManager::Get()->ReleaseTexture(mSkyTextureId);
	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mPlutoMeshBuf.Terminate();
	mNeptuneMeshBuf.Terminate();
	mUranusMeshBuf.Terminate();
	mSaturnMeshBuf.Terminate();
	mJupiterMeshBuf.Terminate();
	mMarsMeshBuf.Terminate();
	mMoonMeshBuf.Terminate();
	mEarthMeshBuf.Terminate();
	mVenusMeshBuf.Terminate();
	mMercuryMeshBuf.Terminate();
	mSunMeshBuf.Terminate();
	mSkyMeshBuf.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	mMercuryRotation += mMercurySpinSpeed * deltaTime;
	mVenusRotation += mVenusSpinSpeed * deltaTime;
	mEarthRotation += mEarthSpinSpeed * deltaTime;
	mMoonRotation += mMoonSpinSpeed * deltaTime;
	mMarsRotation += mMarsSpinSpeed * deltaTime;
	mJupiterRotation += mJupiterSpinSpeed * deltaTime;
	mSaturnRotation += mSaturnSpinSpeed * deltaTime;
	mUranusRotation += mUranusSpinSpeed * deltaTime;
	mNeptuneRotation += mNeptuneSpinSpeed * deltaTime;
	mPlutoRotation += mPlutoSpinSpeed * deltaTime;

	mMercuryOrbitRotation += mMercuryOrbitSpeed * deltaTime;
	mVenusOrbitRotation += mVenusOrbitSpeed * deltaTime;
	mEarthOrbitRotation += mEarthOrbitSpeed * deltaTime;
	mMoonOrbitRotation += mMoonOrbitSpeed * deltaTime;
	mMarsOrbitRotation += mMarsOrbitSpeed * deltaTime;
	mJupiterOrbitRotation += mJupiterOrbitSpeed * deltaTime;
	mSaturnOrbitRotation += mSaturnOrbitSpeed * deltaTime;
	mUranusOrbitRotation += mUranusOrbitSpeed * deltaTime;
	mNeptuneOrbitRotation += mNeptuneOrbitSpeed * deltaTime;
	mPlutoOrbitRotation += mPlutoOrbitSpeed * deltaTime;
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mConstantBuffer.BindVS(0);
	mSampler.BindPS(0);

	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	// Helper: pick the real texture or basketball override
	// Usage: BIND_TEX(mEarthTextureId)
	auto bindTex = [&](TextureId realId)
		{
			TextureId id = mUseBasketballTexture ? mBasketballTextureId : realId;
			TextureManager::Get()->BindPS(id, 0);
		};

	// SKY SPHERE =========================================//
	Math::Vector3 camPos = mCamera.GetPosition();
	Math::Matrix4 skyMatWorld = Math::Matrix4::Translation(camPos.x, camPos.y, camPos.z);
	Math::Matrix4 wvp = Math::Transpose(skyMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	// Sky is never replaced by basketball
	TextureManager::Get()->BindPS(mSkyTextureId, 0);
	mSkyMeshBuf.Render();

	// SUN =========================================//
	wvp = Math::Transpose(Math::Matrix4::Identity * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mSunTextureId);
	mSunMeshBuf.Render();

	// MERCURY =========================================//
	Math::Matrix4 mercuryMatRot = Math::Matrix4::RotationY(mMercuryRotation);
	Math::Matrix4 mercuryMatTrans = Math::Matrix4::Translation(mMercuryOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 mercuryMatOrbit = Math::Matrix4::RotationY(mMercuryOrbitRotation);
	Math::Matrix4 mercuryMatWorld = mercuryMatRot * mercuryMatTrans * mercuryMatOrbit;
	wvp = Math::Transpose(mercuryMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mMercuryTextureId);
	mMercuryMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mMercuryOrbitDistance, Math::Vector3::Zero, Colors::White);

	// VENUS =========================================//
	Math::Matrix4 venusMatRot = Math::Matrix4::RotationY(mVenusRotation);
	Math::Matrix4 venusMatTrans = Math::Matrix4::Translation(mVenusOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 venusMatOrbit = Math::Matrix4::RotationY(mVenusOrbitRotation);
	Math::Matrix4 venusMatWorld = venusMatRot * venusMatTrans * venusMatOrbit;
	wvp = Math::Transpose(venusMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mVenusTextureId);
	mVenusMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mVenusOrbitDistance, Math::Vector3::Zero, Colors::White);

	// EARTH =========================================//
	Math::Matrix4 earthMatRot = Math::Matrix4::RotationY(mEarthRotation);
	Math::Matrix4 earthMatTrans = Math::Matrix4::Translation(mEarthOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 earthMatOrbit = Math::Matrix4::RotationY(mEarthOrbitRotation);
	Math::Matrix4 earthMatWorld = earthMatRot * earthMatTrans * earthMatOrbit;
	wvp = Math::Transpose(earthMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mEarthTextureId);
	mEarthMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mEarthOrbitDistance, Math::Vector3::Zero, Colors::White);

	// MOON =========================================//
	Math::Matrix4 moonMatRot = Math::Matrix4::RotationY(mMoonRotation);
	Math::Matrix4 moonMatLocalTrans = Math::Matrix4::Translation(mMoonOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 moonMatLocalOrbit = Math::Matrix4::RotationY(mMoonOrbitRotation);
	Math::Matrix4 moonMatWorld = moonMatRot * moonMatLocalTrans * moonMatLocalOrbit * earthMatTrans * earthMatOrbit;
	wvp = Math::Transpose(moonMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mMoonTextureId);
	mMoonMeshBuf.Render();

	// MARS =========================================//
	Math::Matrix4 marsMatRot = Math::Matrix4::RotationY(mMarsRotation);
	Math::Matrix4 marsMatTrans = Math::Matrix4::Translation(mMarsOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 marsMatOrbit = Math::Matrix4::RotationY(mMarsOrbitRotation);
	Math::Matrix4 marsMatWorld = marsMatRot * marsMatTrans * marsMatOrbit;
	wvp = Math::Transpose(marsMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mMarsTextureId);
	mMarsMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mMarsOrbitDistance, Math::Vector3::Zero, Colors::White);

	// JUPITER =========================================//
	Math::Matrix4 jupiterMatRot = Math::Matrix4::RotationY(mJupiterRotation);
	Math::Matrix4 jupiterMatTrans = Math::Matrix4::Translation(mJupiterOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 jupiterMatOrbit = Math::Matrix4::RotationY(mJupiterOrbitRotation);
	Math::Matrix4 jupiterMatWorld = jupiterMatRot * jupiterMatTrans * jupiterMatOrbit;
	wvp = Math::Transpose(jupiterMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mJupiterTextureId);
	mJupiterMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mJupiterOrbitDistance, Math::Vector3::Zero, Colors::White);

	// SATURN =========================================//
	Math::Matrix4 saturnMatRot = Math::Matrix4::RotationY(mSaturnRotation);
	Math::Matrix4 saturnMatTrans = Math::Matrix4::Translation(mSaturnOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 saturnMatOrbit = Math::Matrix4::RotationY(mSaturnOrbitRotation);
	Math::Matrix4 saturnMatWorld = saturnMatRot * saturnMatTrans * saturnMatOrbit;
	wvp = Math::Transpose(saturnMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mSaturnTextureId);
	mSaturnMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mSaturnOrbitDistance, Math::Vector3::Zero, Colors::White);

	// URANUS =========================================//
	Math::Matrix4 uranusMatRot = Math::Matrix4::RotationY(mUranusRotation);
	Math::Matrix4 uranusMatTrans = Math::Matrix4::Translation(mUranusOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 uranusMatOrbit = Math::Matrix4::RotationY(mUranusOrbitRotation);
	Math::Matrix4 uranusMatWorld = uranusMatRot * uranusMatTrans * uranusMatOrbit;
	wvp = Math::Transpose(uranusMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mUranusTextureId);
	mUranusMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mUranusOrbitDistance, Math::Vector3::Zero, Colors::White);

	// NEPTUNE =========================================//
	Math::Matrix4 neptuneMatRot = Math::Matrix4::RotationY(mNeptuneRotation);
	Math::Matrix4 neptuneMatTrans = Math::Matrix4::Translation(mNeptuneOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 neptuneMatOrbit = Math::Matrix4::RotationY(mNeptuneOrbitRotation);
	Math::Matrix4 neptuneMatWorld = neptuneMatRot * neptuneMatTrans * neptuneMatOrbit;
	wvp = Math::Transpose(neptuneMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mNeptuneTextureId);
	mNeptuneMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mNeptuneOrbitDistance, Math::Vector3::Zero, Colors::White);

	// PLUTO =========================================//
	Math::Matrix4 plutoMatRot = Math::Matrix4::RotationY(mPlutoRotation);
	Math::Matrix4 plutoMatTrans = Math::Matrix4::Translation(mPlutoOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 plutoMatOrbit = Math::Matrix4::RotationY(mPlutoOrbitRotation);
	Math::Matrix4 plutoMatWorld = plutoMatRot * plutoMatTrans * plutoMatOrbit;
	wvp = Math::Transpose(plutoMatWorld * matView * matProj);
	mConstantBuffer.Update(&wvp);
	bindTex(mPlutoTextureId);
	mPlutoMeshBuf.Render();
	SimpleDraw::AddGroundCircle(20, mPlutoOrbitDistance, Math::Vector3::Zero, Colors::White);

	// CAMERA =========================================//
	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Solar System Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	// Basketball texture toggle
	ImGui::Checkbox("Basketball Mode", &mUseBasketballTexture);

	ImGui::Separator();

	// Each planet: spin speed + orbit speed on one row
	if (ImGui::CollapsingHeader("Mercury"))
	{
		ImGui::SliderFloat("Mercury Spin##spin", &mMercurySpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Mercury Orbit##orbit", &mMercuryOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Venus"))
	{
		ImGui::SliderFloat("Venus Spin##spin", &mVenusSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Venus Orbit##orbit", &mVenusOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Earth"))
	{
		ImGui::SliderFloat("Earth Spin##spin", &mEarthSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Earth Orbit##orbit", &mEarthOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Moon"))
	{
		ImGui::SliderFloat("Moon Spin##spin", &mMoonSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Moon Orbit##orbit", &mMoonOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Mars"))
	{
		ImGui::SliderFloat("Mars Spin##spin", &mMarsSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Mars Orbit##orbit", &mMarsOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Jupiter"))
	{
		ImGui::SliderFloat("Jupiter Spin##spin", &mJupiterSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Jupiter Orbit##orbit", &mJupiterOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Saturn"))
	{
		ImGui::SliderFloat("Saturn Spin##spin", &mSaturnSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Saturn Orbit##orbit", &mSaturnOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Uranus"))
	{
		ImGui::SliderFloat("Uranus Spin##spin", &mUranusSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Uranus Orbit##orbit", &mUranusOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Neptune"))
	{
		ImGui::SliderFloat("Neptune Spin##spin", &mNeptuneSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Neptune Orbit##orbit", &mNeptuneOrbitSpeed, 0.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Pluto"))
	{
		ImGui::SliderFloat("Pluto Spin##spin", &mPlutoSpinSpeed, 0.0f, 50.0f);
		ImGui::SliderFloat("Pluto Orbit##orbit", &mPlutoOrbitSpeed, 0.0f, 50.0f);
	}

	ImGui::Separator();
	if (ImGui::Button("Reset All Speeds"))
	{
		mMercurySpinSpeed = 3.0f;   mMercuryOrbitSpeed = 8.0f;
		mVenusSpinSpeed = 1.5f;   mVenusOrbitSpeed = 6.2f;
		mEarthSpinSpeed = 10.5f;  mEarthOrbitSpeed = 5.0f;
		mMoonSpinSpeed = 2.0f;   mMoonOrbitSpeed = 12.0f;
		mMarsSpinSpeed = 10.0f;  mMarsOrbitSpeed = 4.0f;
		mJupiterSpinSpeed = 25.0f;  mJupiterOrbitSpeed = 2.5f;
		mSaturnSpinSpeed = 22.0f;  mSaturnOrbitSpeed = 1.8f;
		mUranusSpinSpeed = 15.0f;  mUranusOrbitSpeed = 1.2f;
		mNeptuneSpinSpeed = 14.0f;  mNeptuneOrbitSpeed = 0.8f;
		mPlutoSpinSpeed = 5.0f;   mPlutoOrbitSpeed = 0.5f;
	}

	ImGui::End();
}

void GameState::UpdateCamera(float deltaTime)
{
	InputSystem* input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
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