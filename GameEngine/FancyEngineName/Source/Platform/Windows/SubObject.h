#pragma once

namespace Win32 {
	class FANCY_ENGINE_API SubObject {
	public:
		SubObject(std::wstring className, std::wstring classTitle, HICON icon);
		~SubObject();

		virtual void RegisterNewClass();
		virtual void Initialize() = 0;


	protected:
		static		LRESULT CALLBACK	SetupMessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static		LRESULT				AssignMessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		virtual		LRESULT				MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		std::wstring	m_Class;
		std::wstring	m_Title;
		HICON			m_Icon;
		HWND			m_Handle;

	public:
		HWND Handle() const { return m_Handle; }

	public:
		void Handle(HWND hWnd) { m_Handle = hWnd; }
	};
}