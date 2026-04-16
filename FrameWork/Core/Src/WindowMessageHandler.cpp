#include "Precompiled.h"
#include "WindowMessageHandler.h"
#include "DebugUtil.h"

using namespace TarsEngine;
using namespace TarsEngine::Core;

void WindowMessageHandler::Hook(HWND window, CallBack cb)
{
    mWindow = window;
    mPreviousCallBack = (CallBack)GetWindowLongPtr(window, GWLP_WNDPROC);
    SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}
void WindowMessageHandler::Unhook()
{
    SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallBack);
    mWindow = nullptr;
}

LRESULT WindowMessageHandler::FowardMessage(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    ASSERT(mPreviousCallBack != nullptr, "WindowMessageHandler: no callback is hooked");
    return CallWindowProcA((WNDPROC)mPreviousCallBack, window, msg, wParam, lParam);
}