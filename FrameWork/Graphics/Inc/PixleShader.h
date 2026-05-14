#pragma once

namespace TarsEngine::Graphics
{
	class PixleShader final
	{
	public:
		void Initialize(const std::filesystem::path& shaderPath);
		void Terminate();
		void Bind();
	private:
		ID3D11PixelShader* mPixelShader = nullptr;
	};

}