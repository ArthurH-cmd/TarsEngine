#include "Precompiled.h" // always include this first in cpp files
#include "TimeUtil.h"

using namespace TarsEngine;
using namespace TarsEngine::Core;

float TimeUtil::GetTime()
{
	static const auto startTime = std::chrono::high_resolution_clock::now(); // gets start time
	const auto currentTime = std::chrono::high_resolution_clock::now(); // gets current time
	const auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count(); // calculates elapsed time in milliseconds
	return milliSeconds / 1000.0f; // milliseconds --> seconds
}
float TimeUtil::GetDeltaTime()
{
	static auto lastCallTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now(); 
	const auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count(); 
	lastCallTime = currentTime; 
	return milliSeconds / 1000.0f; // milliseconds --> seconds
}