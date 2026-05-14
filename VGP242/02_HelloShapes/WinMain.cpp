#include <TarsEngine/Inc/TarsEngine.h>
#include "ShapeStates.h"

int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR , int )
{
	TarsEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	TarsEngine::App& myApp = TarsEngine::MainApp();
	myApp.AddState<ShapeState>("ShapeState");
	myApp.AddState<QuadState>("QuadState");
	myApp.AddState<HouseState>("HouseState");
	myApp.Run(config);

	return 0;

}