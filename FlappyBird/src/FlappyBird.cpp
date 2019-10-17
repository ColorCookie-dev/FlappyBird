#include<stdafx.h>


#define CIRCLE_RADIUS 25

namespace FB = FlappyBird;

FBD2D *pGraphics;
float fWidth = 600, fHeight = 800;
bool gbGameRunning = false, gbJumped = false;

static void HandleGame(ID2D1HwndRenderTarget *pTarget);
static void HandleGamePlay(ID2D1HwndRenderTarget *pTarget);
static void HandleGamePause(ID2D1HwndRenderTarget *pTarget);

int
wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	HWND					hwnd;
	ID2D1HwndRenderTarget	*pTarget;
	ID2D1SolidColorBrush	*pBrush;

	RECT rc = { (long)fWidth, (long)fHeight };

	const wchar_t *wndClassName = L"FlappyBirdClass";
	FB::RegisterWindow(hInstance, FB::WinProc, wndClassName);
	if (!FB::CreateWin(&hwnd, wndClassName, L"Flappy Bird", hInstance, rc))
		return -1;

	pGraphics = (FBD2D*)alloca(sizeof(FBD2D));

	*pGraphics = FBD2D();

	if (!pGraphics->Init(hwnd)) return -1;
	pTarget = pGraphics->GetRenderTarget();

	ShowWindow(hwnd, nCmdShow);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Direct2D
		pTarget->BeginDraw();
		pGraphics->ClearScreen(1.0f, 1.0f, 1.0f);

		HandleGame(pTarget);

		pTarget->EndDraw();
	}

	return 0;
}

void
HandleGame(ID2D1HwndRenderTarget *pTarget)
{

	if (gbGameRunning) HandleGamePlay(pTarget);
	else HandleGamePause(pTarget);
}

void HandleGamePlay(ID2D1HwndRenderTarget *pTarget)
{
	static float y = fHeight / 2, vy = 4;
	const float gravity = 0.4f;

	// If flappy bird hits bottom
	if (y >= (fHeight - 2*CIRCLE_RADIUS))
	{
		y = fHeight / 2;
		vy = 10;
		gbGameRunning = false;
	}

	// if touches the ceiling
	if (y <= CIRCLE_RADIUS)
	{
		y = CIRCLE_RADIUS;
		vy = 0.01f;
	}

	y += vy;

	// If jumped
	if (gbJumped)
	{
		vy = -8.5;
		gbJumped = false;
	}

	vy += gravity;

	pTarget->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(fWidth / 2, y), CIRCLE_RADIUS, CIRCLE_RADIUS),
		pGraphics->pBrush);
}

void HandleGamePause(ID2D1HwndRenderTarget *pTarget)
{
	pTarget->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(fWidth / 2, fHeight / 2), CIRCLE_RADIUS, CIRCLE_RADIUS),
		pGraphics->pBrush);
}