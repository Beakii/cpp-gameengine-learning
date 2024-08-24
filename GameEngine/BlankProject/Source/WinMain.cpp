#include "pch.h"

/* ------------------------------------ */
/*  Global Variables Section            */
/* ------------------------------------ */
#pragma region Global Variables

WCHAR	WindowClass[MAX_NAME_STRING];
WCHAR	WindowTitle[MAX_NAME_STRING];
INT		WindowHeight;
INT		WindowWidth;
HICON	MainIcon;

#pragma endregion
/* ------------------------------------ */


/* ------------------------------------ */
/*  Function Declarations               */
/* ------------------------------------ */
#pragma region Function Declarations
void IntializeGlobalVaraibles();
void CreateWindowClass();
void InitializeWindow();
void WaitForClose();
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#pragma endregion
/* ------------------------------------ */


/* ------------------------------------ */
/*  Windows Operations                  */
/* ------------------------------------ */
#pragma region Windows Operations
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {

	IntializeGlobalVaraibles();
	CreateWindowClass();
	InitializeWindow();
	WaitForClose();

	return 0;
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
#pragma endregion
/* ------------------------------------ */


/* ------------------------------------ */
/*  Functions                           */
/* ------------------------------------ */
#pragma region Functions
void IntializeGlobalVaraibles() {
	LoadString(HInstance(), IDS_PERGAMENAME, WindowTitle, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_STRING);

	WindowHeight = 600;
	WindowWidth = 800;
	MainIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAIN_ICON));
}

void CreateWindowClass() {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wcex.hIcon = MainIcon;
	wcex.hIconSm = MainIcon;

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = WindowProcess;

	RegisterClassEx(&wcex);
}

void InitializeWindow() {
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
	if (!hWnd) {
		MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
	}

	ShowWindow(hWnd, SW_SHOW);
}

void WaitForClose() {
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
#pragma endregion
/* ------------------------------------ */

