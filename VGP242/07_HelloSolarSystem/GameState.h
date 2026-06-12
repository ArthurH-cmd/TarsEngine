#pragma once
#include <TarsEngine/Inc/TarsEngine.h>
class GameState : public TarsEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
private:
	void UpdateCamera(float deltaTime);
	TarsEngine::Graphics::Camera mCamera;
	TarsEngine::Graphics::ConstantBuffer mConstantBuffer;
	TarsEngine::Graphics::VertexShader mVertexShader;
	TarsEngine::Graphics::PixleShader mPixelShader;
	TarsEngine::Graphics::Sampler mSampler;

	// Sky sphere
	TarsEngine::Graphics::TextureId mSkyTextureId;
	TarsEngine::Graphics::MeshBuffer mSkyMeshBuf;

	// Sun
	TarsEngine::Graphics::TextureId mSunTextureId;
	TarsEngine::Graphics::MeshBuffer mSunMeshBuf;

	// Mercury
	TarsEngine::Graphics::TextureId mMercuryTextureId;
	TarsEngine::Graphics::MeshBuffer mMercuryMeshBuf;
	float mMercuryRotation = 0.0f;
	float mMercuryOrbitRotation = 0.0f;
	float mMercuryOrbitDistance = 0.0f;

	// Venus
	TarsEngine::Graphics::TextureId mVenusTextureId;
	TarsEngine::Graphics::MeshBuffer mVenusMeshBuf;
	float mVenusRotation = 0.0f;
	float mVenusOrbitRotation = 0.0f;
	float mVenusOrbitDistance = 0.0f;

	// Earth
	TarsEngine::Graphics::TextureId mEarthTextureId;
	TarsEngine::Graphics::MeshBuffer mEarthMeshBuf;
	float mEarthRotation = 0.0f;
	float mEarthOrbitRotation = 0.0f;
	float mEarthOrbitDistance = 0.0f;

	// Moon
	TarsEngine::Graphics::TextureId mMoonTextureId;
	TarsEngine::Graphics::MeshBuffer mMoonMeshBuf;
	float mMoonRotation = 0.0f;
	float mMoonOrbitRotation = 0.0f;
	float mMoonOrbitDistance = 0.0f;

	// Mars
	TarsEngine::Graphics::TextureId mMarsTextureId;
	TarsEngine::Graphics::MeshBuffer mMarsMeshBuf;
	float mMarsRotation = 0.0f;
	float mMarsOrbitRotation = 0.0f;
	float mMarsOrbitDistance = 0.0f;

	// Jupiter
	TarsEngine::Graphics::TextureId mJupiterTextureId;
	TarsEngine::Graphics::MeshBuffer mJupiterMeshBuf;
	float mJupiterRotation = 0.0f;
	float mJupiterOrbitRotation = 0.0f;
	float mJupiterOrbitDistance = 0.0f;

	// Saturn
	TarsEngine::Graphics::TextureId mSaturnTextureId;
	TarsEngine::Graphics::MeshBuffer mSaturnMeshBuf;
	float mSaturnRotation = 0.0f;
	float mSaturnOrbitRotation = 0.0f;
	float mSaturnOrbitDistance = 0.0f;

	// Uranus
	TarsEngine::Graphics::TextureId mUranusTextureId;
	TarsEngine::Graphics::MeshBuffer mUranusMeshBuf;
	float mUranusRotation = 0.0f;
	float mUranusOrbitRotation = 0.0f;
	float mUranusOrbitDistance = 0.0f;

	// Neptune
	TarsEngine::Graphics::TextureId mNeptuneTextureId;
	TarsEngine::Graphics::MeshBuffer mNeptuneMeshBuf;
	float mNeptuneRotation = 0.0f;
	float mNeptuneOrbitRotation = 0.0f;
	float mNeptuneOrbitDistance = 0.0f;

	// Pluto
	TarsEngine::Graphics::TextureId mPlutoTextureId;
	TarsEngine::Graphics::MeshBuffer mPlutoMeshBuf;
	float mPlutoRotation = 0.0f;
	float mPlutoOrbitRotation = 0.0f;
	float mPlutoOrbitDistance = 0.0f;

	// Basketball override texture
	TarsEngine::Graphics::TextureId mBasketballTextureId;
	bool mUseBasketballTexture = false;

	// Debug speed multipliers (per planet, spin + orbit)
	float mMercurySpinSpeed = 3.0f;   float mMercuryOrbitSpeed = 8.0f;
	float mVenusSpinSpeed = 1.5f;   float mVenusOrbitSpeed = 6.2f;
	float mEarthSpinSpeed = 10.5f;  float mEarthOrbitSpeed = 5.0f;
	float mMoonSpinSpeed = 2.0f;   float mMoonOrbitSpeed = 12.0f;
	float mMarsSpinSpeed = 10.0f;  float mMarsOrbitSpeed = 4.0f;
	float mJupiterSpinSpeed = 25.0f;  float mJupiterOrbitSpeed = 2.5f;
	float mSaturnSpinSpeed = 22.0f;  float mSaturnOrbitSpeed = 1.8f;
	float mUranusSpinSpeed = 15.0f;  float mUranusOrbitSpeed = 1.2f;
	float mNeptuneSpinSpeed = 14.0f;  float mNeptuneOrbitSpeed = 0.8f;
	float mPlutoSpinSpeed = 5.0f;   float mPlutoOrbitSpeed = 0.5f;
};