#pragma once

#ifdef BUILD_DLL
	#define FANCY_ENGINE_API __declspec(dllexport)
#else
	#define FANCY_ENGINE_API __declspec(dllimport)
#endif

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)