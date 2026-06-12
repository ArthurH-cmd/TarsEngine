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
};

class QuadState : public ShapeState
{
public:
    void Update(float deltaTime) override;
protected:
    void CreateShapes() override;
};

class HouseState : public ShapeState
{
public:
    void Update(float deltaTime) override;
protected:
    void CreateShapes() override;
};

class LogoState : public ShapeState
{
public:
    void Update(float deltaTime) override;
protected:
    void CreateShapes() override;
};
