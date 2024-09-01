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

			case WM_NCCREATE:			{ OnNonClientCreate(); }									return true;
			case WM_NCACTIVATE:			{ OnNonClientActivate(LOWORD(wParam) != WA_INACTIVE); }		return true;	
			case WM_NCPAINT:			{ OnNonClientPaint((HRGN)wParam); }							return false;
			case WM_NCLBUTTONDOWN:		{ OnNonClientLeftMouseButtonDown(); }						break;
			case WM_NCLBUTTONDBLCLK:	{ Win32::Utils::MaximizeWindow(Handle()); }					return 0;

			case WM_GETMINMAXINFO:		{ OnGetMinMaxInfo((MINMAXINFO*)lParam); }					return 0;
			case WM_EXITSIZEMOVE:		{ OnExitSizeMove(); }										break;

			case WM_PAINT:				{ OnPaint(); }												break;

			case WM_TIMER:				{ RedrawWindow(); }											break;

		}

		return SubObject::MessageHandler(hWnd, message, wParam, lParam);
	}

	void Window::RedrawWindow() {
		SetWindowPos(Handle(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_NOSENDCHANGING);
		SendMessage(Handle(), WM_PAINT, 0, 0);
	}

	void Window::OnNonClientCreate() {
		SetTimer(Handle(), 1, 60, NULL);
		SetWindowTheme(Handle(), L"", L"");
		Win32::Utils::ModifyClassStyle(Handle(), 0, CS_DROPSHADOW);

		//🗗
		Win32::Caption::AddButton(new CaptionButton(L"X", CB_CLOSE));
		Win32::Caption::AddButton(new CaptionButton(L"🗖", CB_MAXIMIZE));
		Win32::Caption::AddButton(new CaptionButton(L"🗕", CB_MINIMIZE));
	}

	void Window::OnNonClientActivate(bool active) {
		SetActive(active);
	}

	void Window::OnNonClientPaint(HRGN region) {
		HDC hdc = GetDCEx(Handle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USESTYLE);

		RECT rect;
		GetWindowRect(Handle(), &rect);
		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };
		
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, size.cx, size.cy);
		HANDLE hOld = SelectObject(hdc, hBitmap);




		HBRUSH brush = CreateSolidBrush(RGB(46, 46, 46));
		RECT newRect = { 0, 0, size.cx, size.cy };

		FillRect(hdc, &newRect, brush);
		
		if (Active() && !Win32::Utils::IsWindowFullscreen(Handle())) {
			brush = CreateSolidBrush(RGB(0, 100, 150));
			FrameRect(hdc, &newRect, brush);
		}

		PaintCaption(hdc);

		DeleteObject(brush);




		BitBlt(hdc, 0, 0, size.cx, size.cy, hdc, 0, 0, SRCCOPY);

		SelectObject(hdc, hOld);
		DeleteObject(hBitmap);

		ReleaseDC(Handle(), hdc);
	}

	void Window::PaintCaption(HDC hdc) {
		RECT rect;
		GetWindowRect(Handle(), &rect);
		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };

		if (ShowTitle()) {
			RECT rect = { 30, 0, size.cx, 30 };

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, Active() ? RGB(255, 255, 255) : RGB(92,92,92));

			DrawText(hdc, m_Title.c_str(), m_Title.length(), &rect, DT_LEFT | DT_VCENTER| DT_SINGLELINE);
		}

		int spacing = 0;
		POINT pt;
		GetCursorPos(&pt);
		GetWindowRect(Handle(), &rect);
		pt.x -= rect.left;
		pt.y -= rect.top;

		for (auto button : Caption::CaptionButtons()) {
			spacing += button->Width;

			button->Rect = { size.cx - spacing, 0, (size.cx - spacing + button->Width), 30 };
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y) {
				HBRUSH brush;
				if (button->Command == CB_CLOSE) {
					brush = CreateSolidBrush(RGB(182, 21, 35));
				}
				else {
					brush = CreateSolidBrush(RGB(92, 92, 92));
				}

				FillRect(hdc, &button->Rect, brush);
				DeleteObject(brush);
			}

			if (button->Text.compare(L"🗖") == 0 && Win32::Utils::IsWindowFullscreen(Handle())) {
				button->Text = L"🗗";
			}
			else if (button->Text.compare(L"🗗") == 0 && !Win32::Utils::IsWindowFullscreen(Handle())) {
				button->Text = L"🗖";
			}

			DrawText(hdc, button->Text.c_str(), button->Text.length(), &button->Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}

	void Window::OnNonClientLeftMouseButtonDown() {
		POINT pt;
		RECT rect;

		GetCursorPos(&pt);
		GetWindowRect(Handle(), &rect);

		pt.x -= rect.left;
		pt.y -= rect.top;

		for (auto &button : Caption::CaptionButtons()) {
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y) {
				switch (button->Command) {
					case CB_CLOSE:		{ SendMessage(Handle(), WM_CLOSE, 0, 0); }		break;
					case CB_MINIMIZE:	{ ShowWindow(Handle(), SW_MINIMIZE); }			break;
					case CB_MAXIMIZE:	{ Win32::Utils::MaximizeWindow(Handle()); }		break;
				}
			}
		}
	}

	void Window::OnGetMinMaxInfo(MINMAXINFO* minmax) {
		RECT desktop;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop, 0);
		minmax->ptMaxSize.x = (desktop.right - desktop.left);
		minmax->ptMaxSize.y = (desktop.bottom - desktop.top);
		minmax->ptMaxPosition.x = desktop.left;
		minmax->ptMaxPosition.y = desktop.top;
		minmax->ptMinTrackSize.x = 400;
		minmax->ptMinTrackSize.y = 200;
	}

	void Window::OnExitSizeMove() {
		RECT rect;
		GetWindowRect(Handle(), &rect);
		RECT desktop;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop, 0);
		if (rect.top < desktop.top + 10 && !Win32::Utils::IsWindowFullscreen(Handle())) {
			Win32::Utils::MaximizeWindow(Handle());
		}
	}

	void Window::OnPaint() {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Handle(), &ps);

		RECT rect;
		GetClientRect(Handle(), &rect);

		HBRUSH brush = CreateSolidBrush(RGB(36, 36, 36));
		FillRect(hdc, &rect, brush);
		DeleteObject(brush);

		EndPaint(Handle(), &ps);
	}
}