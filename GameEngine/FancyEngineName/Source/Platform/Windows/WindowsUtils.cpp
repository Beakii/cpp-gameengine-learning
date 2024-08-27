#include "Engine.h"
#include "WindowsUtils.h"

namespace Win32 {
	namespace Utils {
		bool AddBitmap(const WCHAR* fileName, HDC hWinDC, INT x, INT y) {
			BITMAP bitmap;
			HDC hLocalDC = CreateCompatibleDC(hWinDC);

			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if (hBitmap == NULL) {
				MessageBox(NULL, L"LoadImage Failed", L"Error", MB_OK);
				return false;
			}
			GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&bitmap));

			SelectObject(hLocalDC, hBitmap);

			if (!BitBlt(hWinDC, x, y, bitmap.bmWidth, bitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY)) {
				MessageBox(NULL, L"BitBlt Failed", L"Error", MB_OK);
				return false;
			}

			::DeleteDC(hLocalDC);
			::DeleteObject(hBitmap);
			return true;
		}
	}
}