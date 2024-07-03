#include "stdafx.h"
#include "05_TileDemo.h"

void TileDemo::Init()
{
	uint spacing = 40;
	uint width = WinMaxWidth / spacing;
	uint height = WinMaxHeight / spacing;

	tm = new TMap(width * 2, height * 2, spacing);
	tm->MakeTSet(TexturePath + L"tile.png", 22, 11);

	//tm->Load(TilePath + "test.data"); // ������ �� �ҷ�����
	//tm->Update(); // ó�� �ѹ��� �ҷ����� ��
}

void TileDemo::Destroy()
{
	SAFE_DELETE(tm);
}

void TileDemo::Update()
{
	tm->Update();
}

void TileDemo::Render()
{
	tm->Render();
}

void TileDemo::PostRender()
{
}

void TileDemo::GUI()
{
	tm->GUI();
}
