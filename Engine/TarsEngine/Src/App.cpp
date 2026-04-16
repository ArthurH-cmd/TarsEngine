#include "Precompiled.h"
#include "App.h"

using namespace TarsEngine;
using namespace TarsEngine::Core;

void App::Run(const AppConfig& config)
{
	// starts the app
	LOG("App Started");
	// For all systems we build initialize all singletons
	Window myWindow;
	myWindow.Initalize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight);

	while (mRunning = true)
	{
		myWindow.ProcessMessage();
		if (!myWindow.isActive())
		{
			Quit();
			continue;
		}
	}
	// main loop

	// when the app is closed, destroy all singletons

	// ends the app
	myWindow.Terminate();
	LOG("App Ended");
}
void App::Quit()
{
	mRunning = false;
}
