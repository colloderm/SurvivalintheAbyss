#include "stdafx.h"
#include "PlayerAsset.h"

void PlayerAsset::Init()
{
	player = new Player({ 600, 360, 0 }, { 300, 300, 1 });
	HpPotion = new ShadedTexture({ 400, 360, 0 }, { 50, 50, 1 }, 0.0f, TexturePath + L"Player/HpPotion.png");

	// 패시브 데이터 가져와서 추가하기
	player->Hp("passive", 10);
}

void PlayerAsset::Destroy()
{
	SAFE_DELETE(HpPotion);
	SAFE_DELETE(player);
}

void PlayerAsset::Update()
{
	player->Move();
	player->Attack();
	player->Defence();
	player->Interaction();
	player->Inventory();


	player->Update();
	HpPotion->Update();
}

void PlayerAsset::Render()
{
	player->Render();
	HpPotion->Render();
}

void PlayerAsset::PostRender()
{
}

void PlayerAsset::GUI()
{
	ImGui::Begin("SurvivalintheAbyss");
	{
		ImGui::Text("Player");
		ImGui::Text("HP : %d", player->characterHp);
		ImGui::Text("ATK : %d", player->characterAttack);
		ImGui::Text("DEF : %d", player->characterDefence);
		ImGui::Text("SPD : %.1f", player->characterSpeed);
		ImGui::Text("Gold : %d", player->Gold);
		ImGui::Text("POTION : %d", potionCount);
		/*ImGui::Text(("score : " + std::to_string(score) + "Point").c_str());
		ImGui::Text("Block Time : %f", curBlockDmgTime);*/
	}
	ImGui::End();
}
