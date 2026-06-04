#pragma once

namespace TarsEngine::Graphics::DebugUI
{
	enum class Theme
	{
		Classic,
		Dark,
		Light
	};

	void StaticInitialize(HWND window,bool docking = false,bool multiViewport = false);
	void StaticTerminate();
	void SetTheme(Theme theme);

	void BeginDraw();
	void EndDraw();
}