#include "Precompiled.h"
#include "PixleShader.h"

#include "GraphicsSystem.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;

void PixleShader::Initialize(const std::filesystem::path& shaderPath)
{
	auto device = GraphicsSystem::Get()->GetDevice();

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		shaderPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("&s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "PIXLE SHADER : Failed to compile shader.");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	ASSERT(SUCCEEDED(hr), "PIXLE SHADER :Failed to create pixel shader.");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void PixleShader::Terminate()
{
	SafeRelease(mPixelShader);
}

void PixleShader::Bind()
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->PSSetShader(mPixelShader, nullptr, 0);
}