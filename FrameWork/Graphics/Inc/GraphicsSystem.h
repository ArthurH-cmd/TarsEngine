#pragma once


namespace TarsEngine::Graphics
{
	class GraphicsSystem final
	{
	public:
		static void StaticInitialize(HWND window,bool fullscreen);
		static void StaticTerminate();
		static GraphicsSystem* Get();

		GraphicsSystem() = default;
		~GraphicsSystem();

		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem(const GraphicsSystem&&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&&) = delete;

		void Initialize(HWND window, bool fullscreen);
		void Terminate();

		void BeginRender();
		void EndRender();

		void ToggleFullscreen(HWND window);
		void Resize(uint32_t width, uint32_t height);

		void ResetRenderTarget();
		void ResetViewport();

		void SetVSync(bool vsync);

		uint32_t GetBackBufferWidth() const;
		uint32_t GetBackBufferHeight() const;
		float GetBackBufferAspectRatio() const;

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();

	private:
		static LRESULT CALLBACK GraphicsSystemMessageHandle(HWND win, UINT msg, WPARAM wParam, LPARAM Lparam);

		ID3D11Device* mD3DDDevice = nullptr;
		ID3D11DeviceContext* mImmediantContext = nullptr;

		IDXGISwapChain* mSwapChain = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;

		ID3D11Texture2D* mDepthStencilBuffer = nullptr;
		ID3D11DepthStencilView* mDepthStencilView = nullptr;

		DXGI_SWAP_CHAIN_DESC mSwapChainDesc{};
		D3D11_VIEWPORT mViewport{};

		UINT mVSync = 1;
	};


	
}