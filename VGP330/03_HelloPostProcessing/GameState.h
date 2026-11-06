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
	TarsEngine::Graphics::DirectionalLight mDirectionalLight;
	TarsEngine::Graphics::StandardEffect mStandardEffect;
	TarsEngine::Graphics::RenderGroup mCharacter01;
	TarsEngine::Graphics::RenderGroup mCharacter02;
	TarsEngine::Graphics::RenderGroup mCharacter03;
	TarsEngine::Graphics::RenderObject mGround;

	TarsEngine::Graphics::RenderTarget mRenderTarget;
	TarsEngine::Graphics::PostProcessingEffect mPostProcessingEffect;
	TarsEngine::Graphics::Texture mCombineTexture;
	TarsEngine::Graphics::RenderObject mScreenQuad;
};