#pragma once

class FBD2D
{
private:
	ID2D1Factory			*pFactory;
	ID2D1HwndRenderTarget	*pTarget;
	float fStroke = 3.0f;

public:
	ID2D1SolidColorBrush	*pBrush;

	FBD2D();
	~FBD2D();

	bool Init(HWND hwnd);
	void SetBrushColor(float r, float g, float b, float a = 1.0f);
	void SetStroke(float stroke = 3.0f);
	
	void ClearScreen(float r, float g, float b);
	ID2D1HwndRenderTarget	*GetRenderTarget();
};