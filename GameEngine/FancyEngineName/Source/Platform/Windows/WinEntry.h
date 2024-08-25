#include "Engine.h"
#include "IApplication.h"

extern IApplication* CreateApplication();

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {

	PerGameSettings gameSettings;

	auto app = CreateApplication();
	app->SetupGame();

	Logger logger;
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