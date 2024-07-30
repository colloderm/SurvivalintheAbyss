#include "stdafx.h"
#include "StartStage.h"

void StartStage::Init()
{
	uint spacing = 40;
	uint width = WinMaxWidth / spacing;
	uint height = WinMaxHeight / spacing;

	tm = new TMap(width * 2, height, spacing);
	tm->MakeTSet(TexturePath + L"StartMap/Tileset_Ground2.png", 10, 11);
	tm2 = new TMap(width * 2, height, spacing);
	tm2->MakeTSet(TexturePath + L"StartMap/Tileset_Road.png", 6, 10);
	/*tm3 = new TMap(width * 2, height, spacing);
	tm3->MakeTSet(TexturePath + L"StartMap/Trees_Bushes.png", 12, 4);*/

	tm->Load(TilePath + "StartStage_1.data");
	tm2->Load(TilePath + "StartStage_2.data"); // 저장한 맵 불러오기
	//tm3->Load(TilePath + "StartStage_3.data");
	tm2->Update(); // 처음 한번만 불러오고 끝

	// 뾰족나무
	TriangleTree = new TextureRect({ 1100, 650, 0 }, { 100, 100, 1 }, 0.0f, TexturePath + L"StartMap/Tree_Emerald_1.png");
	others.push_back(TriangleTree);
	// 둥글나무
	BasicTree = new TextureRect({ 300, 650, 0 }, { 80, 110, 1 }, 0.0f, TexturePath + L"StartMap/Tree_Emerald_2.png");
	others.push_back(BasicTree);
	// 더블나무
	DoubleTree = new TextureRect({ 400, 650, 0 }, { 90, 150, 1 }, 0.0f, TexturePath + L"StartMap/Tree_Emerald_3.png");
	others.push_back(DoubleTree);
	// 긴나무
	LongTree = new TextureRect({ 500, 650, 0 }, { 70, 150, 1 }, 0.0f, TexturePath + L"StartMap/Tree_Emerald_4.png");
	others.push_back(LongTree);

	BlacksmithShop = new TextureRect({ 950, 630, 0 }, { 230, 200, 1 }, 0.0f, TexturePath + L"StartMap/BlacksmithShop.png");
	SorceryShop = new TextureRect({ 120, 430, 0 }, { 230, 200, 1 }, 0.0f, TexturePath + L"StartMap/SorceryShop.png");
	ItemShop = new TextureRect({ 650, 230, 0 }, { 230, 230, 1 }, 0.0f, TexturePath + L"StartMap/ItemShop.png");
}

void StartStage::Destroy()
{
	SAFE_DELETE(ItemShop);
	SAFE_DELETE(SorceryShop);
	SAFE_DELETE(BlacksmithShop);
	for (auto other : others)
		SAFE_DELETE(other);
	//SAFE_DELETE(tm3);
	SAFE_DELETE(tm2);
	SAFE_DELETE(tm);
}

void StartStage::Update()
{
	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Press(VK_F3))
		{
			TextureRect* tt = new TextureRect(Camera::Get()->GetMPosition(), woodSize, 0.0f, woodPath);
			others.push_back(tt);
		}
	}

	if (Mouse::Get()->Press(0x00000000))
	{
		others[others.size() - 1]->SetPosition(Camera::Get()->GetMPosition());
	}

	for (auto other : others)
		other->Update();
	BlacksmithShop->Update();
	SorceryShop->Update();
	ItemShop->Update();
}

void StartStage::Render()
{
	tm2->Render();
	tm->Render();
	for (auto other : others)
		other->Render();
	BlacksmithShop->Render();
	SorceryShop->Render();
	ItemShop->Render();
}

void StartStage::PostRender()
{
}

void StartStage::GUI()
{
	//tm2->GUI();
	ImGui::Begin("StageMaker");
	{
		Texture2D* t = new Texture2D(TexturePath + L"StartMap/Tree_Emerald_1.png");
		if (ImGui::ImageButton(t->GetSRV(), { 20,20 }))
		{
			woodPath = TexturePath + L"StartMap/Tree_Emerald_1.png";
			woodSize = { 100, 100, 1 };
		}
		Texture2D* t2 = new Texture2D(TexturePath + L"StartMap/Tree_Emerald_2.png");
		if (ImGui::ImageButton(t2->GetSRV(), { 20,20 }))
		{
			woodPath = TexturePath + L"StartMap/Tree_Emerald_2.png";
			woodSize = { 80, 110, 1 };
		}
		Texture2D* t3 = new Texture2D(TexturePath + L"StartMap/Tree_Emerald_3.png");
		if (ImGui::ImageButton(t3->GetSRV(), { 20,20 }))
		{
			woodPath = TexturePath + L"StartMap/Tree_Emerald_3.png";
			woodSize = { 90, 150, 1 };
		}
		Texture2D* t4 = new Texture2D(TexturePath + L"StartMap/Tree_Emerald_4.png");
		if (ImGui::ImageButton(t4->GetSRV(), { 20,20 }))
		{
			woodPath = TexturePath + L"StartMap/Tree_Emerald_4.png";
			woodSize = { 70, 150, 1 };
		}
	}
	ImGui::End();
}
