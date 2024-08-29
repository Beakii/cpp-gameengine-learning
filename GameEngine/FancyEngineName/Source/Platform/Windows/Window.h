#pragma once

#include "SubObject.h"

namespace Win32 {
	class FANCY_ENGINE_API Window : public Win32::SubObject {
	public:
		Window(std::wstring title, HICON icon, WindowType type = RESIZEABLE);
		~Window();

		virtual		void		Initialize() override;
		virtual		LRESULT		MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

		void RedrawWindow();

		void OnNonClientCreate();
		void OnNonClientPaint(HRGN region);


	protected:
		SIZE		m_Size;
		WindowType	m_WindowType;

	public:
		SIZE Size() const { return m_Size; }

	public:
		void SetSize(SIZE size) { m_Size = size; }
		void SetSize(int cx, int cy) { m_Size.cx = cx; m_Size.cy = cy; }
	};
}