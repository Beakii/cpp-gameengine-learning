#pragma once

#include "Platform/Windows/Window.h"

namespace SplashScreen {
	void FANCY_ENGINE_API Open();
	void FANCY_ENGINE_API Close();
	void FANCY_ENGINE_API AddMessage(const WCHAR* message);
}

class FANCY_ENGINE_API SplashWindow : public Win32::Window {
public:
	SplashWindow();
	~SplashWindow();

	virtual	LRESULT	MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	WCHAR m_outputMessage[MAX_NAME_STRING];
};