#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace TarsEngine;
using namespace TarsEngine::Core;
using namespace TarsEngine::Input;

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

	auto handle = myWindow.GetWindowsHandle();
	InputSystem::StaticInitialize(handle);

	ASSERT(mCurrentState != nullptr, "App: AppState is not set!");
	mCurrentState->Initialize();

	InputSystem* input = InputSystem::Get();

	mRunning = true;

	while (mRunning)
	{
		myWindow.ProcessMessage();
		input->Update();
		if (!myWindow.isActive() || input->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		float deltaTime = TimeUtil::GetDeltaTime();

#if defined(_DEBUG)

		if (deltaTime > 0.5f)
		{
			LOG("App: rly long delta time, skipping frames %f", deltaTime);
			continue;
		}
#endif 
		mCurrentState->Update(deltaTime);

		// render flow
	}

	// terminate the Active State
	mCurrentState->Terminate();
	// main loop

	// when the app is closed, destroy all singletons
	InputSystem::StaticTerminate();
	// ends the app

	myWindow.Terminate();
	LOG("App Ended");
}

void App::Quit()
{
	mRunning = false;
}

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}