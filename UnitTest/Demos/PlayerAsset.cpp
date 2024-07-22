#include "stdafx.h"
#include "PlayerAsset.h"

void PlayerAsset::Init()
{
	player = new Player({ 600, 360, 0 }, { 300, 300, 1 });
	HpPotion = new ShadedTexture({ 400, 360, 0 }, { 50, 50, 1 }, 0.0f, TexturePath + L"Player/HpPotion.png");

	// 패시브 데이터 가져와서 추가하기
	player->Hp("passive", 10);

	zombie = new Zombie({ 300,300,0 }, { 200,200,1 });

	player->SetTarget(zombie->GetDmgRect());

	pPassive = new PlayerPassive();
	pPassive->PsvLoad(PsvPath + "PlayerPassive.data");
	player->SetPassive(pPassive);
}

void PlayerAsset::Destroy()
{
	SAFE_DELETE(pPassive);
	SAFE_DELETE(zombie);
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

	/*if (bool temp = true)
	{
		pPassive->PsvLoad(PsvPath + "PlayerPassive.data");

		player->SetPassive(pPassive);

		temp = false;
	}*/

	pPassive->Update();

	player->Update();
	HpPotion->Update();

	zombie->Update();
}

void PlayerAsset::Render()
{
	zombie->Render();

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
		ImGui::Text("HP : %d + %d", player->characterHp, pPassive->GetPsvHp());
		ImGui::Text("ATK : %d + %d", player->characterAttack, pPassive->GetPsvAtk());
		ImGui::Text("DEF : %d + %d", player->characterDefence, pPassive->GetPsvDef());
		ImGui::Text("SPD : %.1f + %.1f", player->characterSpeed, pPassive->GetPsvSpd());
		ImGui::Text("Gold : %d", player->Gold);
		ImGui::Text("POTION : %d", potionCount);
		/*ImGui::Text(("score : " + std::to_string(score) + "Point").c_str());*/

		ImGui::Text("#################################");

		ImGui::Text("Monster");
		ImGui::Text("HP : %d", zombie->characterHp);
	}
	ImGui::End();
}
