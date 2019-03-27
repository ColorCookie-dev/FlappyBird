#include<stdafx.h>


// SafeRelease
template<typename T>
void SafeRelease(T **res)
{
	if (!res)
	{
		(*res)->Release();
		(*res) = nullptr;
	}
}


FBD2D::FBD2D()
{
	pBrush = NULL;
	pTarget = NULL;
	pFactory = NULL;
}


bool FBD2D::Init(HWND hwnd)
{
	if (!pFactory)
	{
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
		if (hr != S_OK) return false;

		if (!pTarget)
		{
			RECT rc = {};
			if (!GetClientRect(hwnd, &rc)) return false;

			hr = pFactory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(
					hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
				&pTarget);
			if (hr != S_OK) return false;

			hr = pTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &pBrush);
			if (FAILED(hr)) return false;

			return true;
		}
	}
	return false;
}


// Setters
void
FBD2D::ClearScreen(float r, float g, float b)
{ pTarget->Clear(D2D1::ColorF(r, g, b)); }

void
FBD2D::SetBrushColor(float r, float g, float b, float a)
{ pBrush->SetColor(D2D1::ColorF(r, g, b, a)); }

void
FBD2D::SetStroke(float stroke)
{ fStroke = stroke; }


// Getters
ID2D1HwndRenderTarget*
FBD2D::GetRenderTarget()
{ return pTarget; }


FBD2D::~FBD2D()
{
	SafeRelease(&pBrush);
	SafeRelease(&pTarget);
	SafeRelease(&pFactory);
}