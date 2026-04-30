#include <TarsEngine/Inc/TarsEngine.h>
#include "ShapeStates.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TarsEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	TarsEngine::App& myApp = TarsEngine::MainApp();
	myApp.AddState<ShapeState>("ShapeState");
	myApp.Run(config);

	return 0;

}