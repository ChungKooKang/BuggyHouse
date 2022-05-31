#include "BuggyHouse.h"

HRESULT BuggyHouse::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	HRESULT hr;
	hr = D2DFramework::Initialize(hInstance, title, width, height);
	

	mspBackground = std::make_unique<Actor>(this, L"Data/back1_1024.png", 0.0f, 0.0f);
	
	float sx{}, sy{};
	RECT rct{};
	GetClientRect(mHwnd, &rct);

	for (int i = 0; i < 40; i++)
	{
		sx = static_cast<float>(rand() % (rct.right - rct.left));
		sy = static_cast<float>(rand() % (rct.bottom - rct.top));
		mspbugList.push_back(
			std::make_unique<Actor>(this, L"Data/bug1_1.png", sx, sy)
		);

	}
	return S_OK;
}

void BuggyHouse::Release()
{
	for (auto& e : mspbugList)
	{
		e.reset();
	}

	mspbugList.clear();
	mspBackground.reset();

	D2DFramework::Release();
}

void BuggyHouse::Render()
{
	HRESULT hr;

	mspRenderTarget->BeginDraw();

	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
	mspBackground->Draw();

	for (auto& e : mspbugList)
	{
		auto pt = e->GetPosition();
		pt.x += static_cast<float>(1 - rand() % 3);
		pt.y += static_cast<float>(1 - rand() % 3);
		e->SetPosition(pt);
		e->Draw();
	}
	
	hr = mspRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}

}
