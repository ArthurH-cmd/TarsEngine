#pragma once

namespace TarsEngine::Core
{
	class Window
	{
	public:
		void Initalize(HINSTANCE instance, const std::wstring& appName, uint32_t width, uint32_t height);
		void Terminate();

		void ProcessMessage();

		HWND GetWindowsHandle() const;
		bool isActive() const;
	private:
		HINSTANCE mInstance = nullptr;
		HWND mWindow = nullptr;
		RECT mScreenRect = {};
		std::wstring mAppName;
		bool mIsActive = false;
		
	};
}