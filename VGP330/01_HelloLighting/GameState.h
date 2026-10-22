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
	TarsEngine::Graphics::StandardEffect mStandardEffectCel;
	TarsEngine::Graphics::RenderTarget mRenderTarget;

	TarsEngine::Graphics::RenderObject mRenderObject;
	TarsEngine::Graphics::RenderObject mRenderObject2;
	bool mUseCellShading = false;
};