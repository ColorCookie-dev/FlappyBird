#include<stdafx.h>


namespace FB = FlappyBird;

int
wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	HWND					hwnd;
	FBD2D					Graphics;
	ID2D1HwndRenderTarget	*pTarget;
	ID2D1SolidColorBrush	*pBrush;

	const wchar_t *wndClassName = L"FlappyBirdClass";
	FB::RegisterWindow(hInstance, FB::WinProc, wndClassName);
	if (!FB::CreateWin(&hwnd, wndClassName, L"Flappy Bird", hInstance))
		return -1;

	Graphics.Init(hwnd);
	pTarget = Graphics.GetRenderTarget();

	ShowWindow(hwnd, nCmdShow);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) continue;
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Direct2D
		pTarget->BeginDraw();
		Graphics.ClearScreen(1.0f, 1.0f, 1.0f);

		pTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(5, 10), 10, 10), Graphics.pBrush);

		pTarget->EndDraw();
	}

	return 0;
}