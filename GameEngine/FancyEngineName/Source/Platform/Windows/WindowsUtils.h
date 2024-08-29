#pragma once

#define DEFAULT_HEIGHT 600
#define DEFAULT_WIDTH 800

namespace Win32 {

	enum WindowType : DWORD {
		STATIC		= WS_OVERLAPPED,
		RESIZEABLE	= WS_SIZEBOX,
		POPUP		= WS_POPUP,
	};

	namespace Utils {

		bool FANCY_ENGINE_API AddBitmap(const WCHAR* fileName, HDC hWinDC, INT x = 0, INT y = 0);
	}
}