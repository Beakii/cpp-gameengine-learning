#include "Engine.h"
#include "SubObject.h"

namespace Win32 {
	SubObject::SubObject(std::wstring className, std::wstring classTitle, HICON icon)
		: m_Class(className), m_Title(classTitle), m_Icon(icon)
	{
	}

	SubObject::~SubObject()
	{
	}

	void SubObject::RegisterNewClass() {
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;

		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(36, 36, 36)));

		wcex.hIcon = m_Icon;
		wcex.hIconSm = m_Icon;

		wcex.lpszClassName = m_Class.c_str();

		wcex.lpszMenuName = nullptr;

		wcex.hInstance = HInstance();

		wcex.lpfnWndProc = SetupMessageHandler;

		RegisterClassEx(&wcex);
	}

	LRESULT SubObject::SetupMessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		if (message == WM_NCCREATE) {
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Win32::SubObject* const pWnd = static_cast<Win32::SubObject*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32::SubObject::AssignMessageHandler));
			pWnd->Handle(hWnd);
			return pWnd->MessageHandler(hWnd, message, wParam, lParam);
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	LRESULT SubObject::AssignMessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		Win32::SubObject* const pWnd = reinterpret_cast<Win32::SubObject*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->MessageHandler(hWnd, message, wParam, lParam);
	}

	LRESULT SubObject::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

