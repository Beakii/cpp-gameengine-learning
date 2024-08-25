#pragma once
#include <string>

class FANCY_ENGINE_API Logger {
private:
	static Logger* instance;
public:
	static Logger* Instance() { return instance; }


public:
	Logger();
	~Logger();

	static void Log(const WCHAR* message, ...);
	static std::wstring LogDirectory();
	static std::wstring LogFile();

	static void PrintDebugSeperator();
	
	static bool IsMTailRunning();
	static void StartMTail();
};