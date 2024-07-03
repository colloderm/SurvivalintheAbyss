#include "stdafx.h"
#include "00_RectDemo.h"

void RectDemo::Init()
{
	// 2D에서는 위치의 z가 0이고 크기의 z가 1이어야 두깨가 생기며 카메라에 그려질 수 있다.
	r = new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(100, 100, 1));
}

void RectDemo::Destroy()
{
	SAFE_DELETE(r);
}

void RectDemo::Update()
{
	r->Update();
	r->Move();
}

void RectDemo::Render()
{
	r->Render();
}

void RectDemo::PostRender()
{
}

void RectDemo::GUI()
{
	r->GUI();
}
