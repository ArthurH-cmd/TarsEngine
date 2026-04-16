#include "Precompiled.h"
#include "TarsEngine.h"

TarsEngine::App& TarsEngine::MainApp()
{
	static App sApp;
	return sApp;
}