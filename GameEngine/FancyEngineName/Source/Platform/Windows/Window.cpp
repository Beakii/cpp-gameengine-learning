#include "Engine.h"
#include "Window.h"

#define DCX_USESTYLE 0x00010000

namespace Win32 {
	Window::Window(std::wstring title, HICON icon, WindowType type)
		: Win32::SubObject(title, title, icon), m_WindowType(type)
	{
		SetSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	}

	Window::~Window()
	{
	}

	void Window::Initialize()
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT rect = { 0, 0, Size().cx, Size().cy};
		AdjustWindowRect(&rect, m_WindowType, false);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		m_Handle = CreateWindow(m_Class.c_str(), m_Title.c_str(), m_WindowType,
			((desktop.right / 2) - (Size().cx / 2)), ((desktop.bottom / 2) - (Size().cy / 2)), Size().cx, Size().cy, 0, 0, HInstance(), (void*)this);

		if (!m_Handle) {
			MessageBox(0, L"Failed to create window.", 0, 0);
			PostQuitMessage(0);
		}

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
	}

	LRESULT Window::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {

			case WM_NCCREATE:	{ OnNonClientCreate(); }				return true;
			case WM_NCPAINT:	{ OnNonClientPaint((HRGN)wParam); }		return false;
			case WM_TIMER:		{ RedrawWindow(); }						break;

		}

		return SubObject::MessageHandler(hWnd, message, wParam, lParam);
	}

	void Window::RedrawWindow() {
		SetWindowPos(Handle(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_NOSENDCHANGING);
		SendMessage(Handle(), WM_PAINT, 0, 0);
	}

	void Window::OnNonClientCreate() {
		SetTimer(Handle(), 1, 60, NULL);
	}

	void Window::OnNonClientPaint(HRGN region) {
		HDC hdc = GetDCEx(Handle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USESTYLE);

		RECT rect;
		GetWindowRect(Handle(), &rect);

		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };
		RECT newRect = { 0, 0, size.cx, size.cy };


		HBRUSH brush = CreateSolidBrush(RGB(46, 46, 46));

		FillRect(hdc, &newRect, brush);
		DeleteObject(brush);

		ReleaseDC(Handle(), hdc);
	}
}

