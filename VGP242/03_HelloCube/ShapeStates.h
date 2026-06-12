#pragma once

#include <TarsEngine/Inc/TarsEngine.h>

class ShapeState : public TarsEngine::AppState
{
public: 
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Render() override;
protected:
    virtual void CreateShapes();

    using Vertices = std::vector<TarsEngine::Graphics::VertexPC>;
    Vertices mVertices;

    TarsEngine::Graphics::MeshBuffer mMeshBuffer;
    TarsEngine::Graphics::VertexShader mVertexShader;
    TarsEngine::Graphics::PixleShader mPixelShader;
    TarsEngine::Graphics::Camera mCamera;
    TarsEngine::Graphics::ConstantBuffer mConstantBuffer;
};
