#pragma once

namespace FlappyBird
{
	LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	ATOM RegisterWindow(HINSTANCE hInstance,
		LRESULT(*WinProcFunc)(HWND, UINT, WPARAM, LPARAM),
		const wchar_t *className);

	bool CreateWin(HWND *pHwnd, const wchar_t *className, const wchar_t *winName,
		HINSTANCE hInstance, RECT rc);
}