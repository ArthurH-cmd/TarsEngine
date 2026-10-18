#include "Precompiled.h"
#include "RenderTarget.h"
#include "GraphicsSystem.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;

namespace
{
	DXGI_FORMAT GetDXGIFormat(RenderTarget::Format format)
	{
		switch (format)
		{
			case RenderTarget::Format::RGBA_UB:   return DXGI_FORMAT_R8G8B8A8_UNORM;
			case RenderTarget::Format::RGBA_U32:  return DXGI_FORMAT_R32G32B32A32_UINT;
		default:
			assert(false && "Unknown format.");
			break;
		}
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}
}


RenderTarget::~RenderTarget()
{

}

void RenderTarget::Initialize(const std::filesystem::path& fileName)
{
	

}

void RenderTarget::Initialize(uint32_t width, uint32_t height, Format format)
{
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = GetDXGIFormat(format);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	auto device = GraphicsSystem::Get()->GetDevice();
	ID3D11Texture2D* texture = nullptr;
	HRESULT hr = device->CreateTexture2D(&desc, nullptr, &texture);
	ASSERT(SUCCEEDED(hr), "Failed to create texture for render target.");

	hr = device->CreateShaderResourceView(texture, nullptr, &mShaderResourceView);
	ASSERT(SUCCEEDED(hr), "Failed to create shader resource view for render target.");

	hr = device->CreateRenderTargetView(texture, nullptr, &mRenderTargetView);
	ASSERT(SUCCEEDED(hr), "Failed to create Target resource view for render target.");

	SafeRelease(texture);

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	hr = device->CreateTexture2D(&desc, nullptr, &texture);
	ASSERT(SUCCEEDED(hr), "Failed to create depth stencil texture for render target.");

	hr = device->CreateDepthStencilView(texture, nullptr, &mDepthStencilView);
	ASSERT(SUCCEEDED(hr), "Failed to create depth stencil view for render target.");

	SafeRelease(texture);

	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;
	mViewport.Width = static_cast<float>(width);
	mViewport.Height = static_cast<float>(height);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;

}

void RenderTarget::Terminate() 
{
	Texture::Terminate();

	SafeRelease(mDepthStencilView);
	SafeRelease(mRenderTargetView);
}

void RenderTarget::BeginRender(const Color& clearColor)
{
	auto context = GraphicsSystem::Get()->GetContext();

	UINT numViewports = 1;
	context->OMSetRenderTargets(1, &mRenderTargetView, mOldDepthStencilView);
	context->RSGetViewports(&numViewports, &mOldViewport);

	context->ClearRenderTargetView(mRenderTargetView, &clearColor.r);
	context->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f,0.0f);
	context->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	context->RSSetViewports(1, &mViewport);
}

void RenderTarget::EndRender()
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->OMSetRenderTargets(1, &mOldRenderTargetView, mOldDepthStencilView);
	context->RSSetViewports(1, &mOldViewport);

	SafeRelease(mOldRenderTargetView);
	SafeRelease(mOldDepthStencilView);
}
