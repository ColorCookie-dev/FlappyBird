#include<stdafx.h>

LRESULT CALLBACK FlappyBird::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool FlappyBird::CreateWin(HWND *pHwnd, const wchar_t *className, const wchar_t *winName,
	HINSTANCE hInstance)
{
	RECT rc = { 600, 800 };
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, NULL, NULL);
	(*pHwnd) = CreateWindowEx(NULL,
		className,
		winName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right + rc.left, rc.bottom + rc.top,
		NULL, NULL, hInstance, NULL);

	if ((*pHwnd) == NULL) return false;
	return true;
}

ATOM FlappyBird::RegisterWindow(HINSTANCE hInstance,
	LRESULT(*WinProcFunc)(HWND, UINT, WPARAM, LPARAM),
	const wchar_t *className)
{
	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	wc.lpfnWndProc = WinProcFunc;

	return RegisterClass(&wc);
}