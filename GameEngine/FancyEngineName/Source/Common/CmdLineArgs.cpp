#include "Engine.h"
#include "CmdLineArgs.h"
#include <algorithm>

void CmdLineArgs::ReadArguments() {
	int argCount = 0;
	LPWSTR* argList = CommandLineToArgvW(GetCommandLineW(), &argCount);

	for (int i = 1; i < argCount; i++) {
		std::wstring key = argList[i];

		if (key[0] == '-') {
			key.erase(0, 1);
			std::transform(key.begin(), key.end(), key.begin(), ::tolower);
			ReadArgument(key.c_str());
		}
	}
}

void CmdLineArgs::ReadArgument(const WCHAR* key) {
	if (wcscmp(key, L"mtail") == 0) {
		Logger::StartMTail();
	}
}
