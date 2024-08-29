#include "Engine.h"
#include "SplashScreen.h"

#include "Platform/Windows/WindowsUtils.h"

namespace SplashScreen {

#define WM_OUTPUTMESSAGE (WM_USER + 0x0001)

	SplashWindow* m_SplashWindow;

	void Open()
	{
		if (m_SplashWindow != nullptr)
		{
			return;
		}
		m_SplashWindow = new SplashWindow();
	}

	void Close()
	{
		return void FANCY_ENGINE_API();
	}

	void AddMessage(const WCHAR* message)
	{
		PostMessage(m_SplashWindow->Handle(), WM_OUTPUTMESSAGE,(WPARAM)message, 0);
	}
}



SplashWindow::SplashWindow()
	: Win32::Window(L"SplashWindow", NULL, Win32::WindowType::POPUP)
{
	wcscpy_s(m_outputMessage, L"Splash Screen Starting...");
	Win32::Window::RegisterNewClass();
	SetSize(500, 600);
	Win32::Window::Initialize();
}

SplashWindow::~SplashWindow()
{
}

LRESULT SplashWindow::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PAINT: {
		HBITMAP hBitmap;
		HDC hdc, hdcMem;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hWnd, &ps);

		Win32::Utils::AddBitmap(PerGameSettings::GameSplashURL(), hdc, 0, 0);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if (EngineConfig::GetMode() != EngineConfig::EngineMode::RELEASE) {
			std::wstring engineModeText = EngineConfig::EngineModeToString() + L" MODE";
			SetTextAlign(hdc, TA_RIGHT);
			TextOut(hdc, (Size().cx - 15), 15, engineModeText.c_str(), engineModeText.length());
		}

		SetTextAlign(hdc, TA_CENTER);

		TextOut(hdc, (Size().cx / 2), (Size().cy - 30), m_outputMessage, wcslen(m_outputMessage));
		EndPaint(hWnd, &ps);
	}
		break;

	case WM_OUTPUTMESSAGE: {
		WCHAR* msg = (WCHAR*)lParam;
		wcscpy_s(m_outputMessage, msg);
		RedrawWindow();
	}
	}

	return Window::MessageHandler(hWnd, message, wParam, lParam);
}
