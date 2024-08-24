#include <Windows.h>

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

WCHAR	WindowClass[MAX_NAME_STRING];
WCHAR	WindowTitle[MAX_NAME_STRING];

INT		WindowHeight;
INT		WindowWidth;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	
#pragma region Init Global Variables

	wcscpy_s(WindowClass, TEXT("SomethingCool"));
	wcscpy_s(WindowTitle, TEXT("Yahoo"));
	WindowHeight = 800;
	WindowWidth = 600;

#pragma endregion

#pragma region Create Window Class

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcex);

#pragma endregion

#pragma region Create and Display Window

	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
	if (!hWnd) {
		MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

#pragma endregion

#pragma region Loop to prevent close

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

#pragma endregion

	return 0;
}