#include "stdafx.h"
#include "00_RectDemo.h"

void RectDemo::Init()
{
	// 2D������ ��ġ�� z�� 0�̰� ũ���� z�� 1�̾�� �α��� ����� ī�޶� �׷��� �� �ִ�.
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
