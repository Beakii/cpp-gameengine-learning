#include "Engine.h"

#include "IApplication.h"
#include "Common/CmdLineArgs.h"

extern Win32::IApplication* CreateApplication();

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {

	PerGameSettings gameSettings;

	auto app = CreateApplication();
	app->SetupGame();

	CmdLineArgs::ReadArguments();

	Logger logger;

	app->PreInitialize();

	app->Initialize();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			app->Update();
		}
	}

	return 0;
}