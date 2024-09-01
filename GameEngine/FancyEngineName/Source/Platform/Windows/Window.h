#pragma once

#include "SubObject.h"

#include <Uxtheme.h>
#pragma comment(lib, "Uxtheme.lib")

namespace Win32 {
	class FANCY_ENGINE_API Window : public Win32::SubObject, public Win32::Caption {
	public:
		Window(std::wstring title, HICON icon, WindowType type = RESIZEABLE);
		~Window();

		virtual		void		Initialize() override;
		virtual		LRESULT		MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

		void RedrawWindow();
		void OnNonClientCreate();
		void OnNonClientActivate(bool active);
		void OnNonClientPaint(HRGN region);
		void PaintCaption(HDC hdc);
		void OnNonClientLeftMouseButtonDown();
		void OnGetMinMaxInfo(MINMAXINFO* minmax);
		void OnExitSizeMove();
		void OnPaint();


	protected:
		SIZE		m_Size;
		WindowType	m_WindowType;

		bool		m_Active;

	public:
		SIZE Size() const { return m_Size; }
		bool Active() const { return m_Active; }

	public:
		void SetSize(SIZE size) { m_Size = size; }
		void SetSize(int cx, int cy) { m_Size.cx = cx; m_Size.cy = cy; }
		void SetActive(bool active) { m_Active = active; }
	};
}