#pragma once

#include "TimeUtil.h"

using namespace TarsEngine;
using namespace TarsEngine::Core;

#if defined(_DEBUG) // check if we are in debug mode

#define LOG(format, ...);\
	do {\
		char buf[256];\
		int _res = snprintf(buf,std::size(buf),"{%.3f}: "##format##"\n", TimeUtil::GetTime(), __VA_ARGS__);\
		OutputDebugStringA(buf);\
	}while(false)

#define ASSERT(condition, format, ...);\
	do {\
		if (!(condition))\
		{\
			LOG("ASSERT: %s(%d): "##format, __FILE__, __LINE__, __VA_ARGS__); \
			DebugBreak();\
		}\
	}while(false)

#else // skips if not in debug mode

#define LOG(format, ...)
#define ASSERT(condition, format, ...) do { (void)sizeof(condition); } while(false)
#endif