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

		/*if (pPassive->PsvCount() > 0)
		{*/
			// HP
			if (pPassive->GetIncHpCount() < 10 && ImGui::Button("Increase HP"))
			{
				pPassive->SetIncHpCount(1);
				pPassive->SetIncHp(10);
			}
			ImGui::SameLine();
			if (pPassive->GetIncHpCount() > 0 && ImGui::Button("Decrease HP"))
			{
				pPassive->SetIncHpCount(-1);
				pPassive->SetIncHp(-10);
			}
			ImGui::SameLine();
			ImGui::Text("HP: %d / HPCount: %d", pPassive->GetPsvHp(), pPassive->GetIncHpCount());

			// Attack
			if (pPassive->GetIncAtkCount() < 10 && ImGui::Button("Increase Attack"))
			{
				pPassive->SetIncAtkCount(1);
				pPassive->SetIncAtk(5);
			}
			ImGui::SameLine();
			if (pPassive->GetIncAtkCount() > 0 && ImGui::Button("Decrease Attack"))
			{
				pPassive->SetIncAtkCount(-1);
				pPassive->SetIncAtk(-5);
			}
			ImGui::SameLine();
			ImGui::Text("Attack: %d / AttackCount: %d", pPassive->GetPsvAtk(), pPassive->GetIncAtkCount());

			// Defence
			if (pPassive->GetIncDefCount() < 10 && ImGui::Button("Increase Defence"))
			{
				pPassive->SetIncDefCount(1);
				pPassive->SetIncDef(5);
			}
			ImGui::SameLine();
			if (pPassive->GetIncDefCount() > 0 && ImGui::Button("Decrease Defence"))
			{
				pPassive->SetIncDefCount(-1);
				pPassive->SetIncDef(-5);
			}
			ImGui::SameLine();
			ImGui::Text("Defence: %d / DefenceCount: %d", pPassive->GetPsvDef(), pPassive->GetIncDefCount());

			// Speed
			if (pPassive->GetIncSpdCount() < 10 && ImGui::Button("Increase Speed"))
			{
				pPassive->SetIncSpdCount(1);
				pPassive->SetIncSpd(0.2f);
			}
			ImGui::SameLine();
			if (pPassive->GetIncSpdCount() > 0 && ImGui::Button("Decrease Speed"))
			{
				pPassive->SetIncSpdCount(-1);
				pPassive->SetIncSpd(-0.2f);
			}
			ImGui::SameLine();
			ImGui::Text("Speed: %.1f / SpeedCount: %d", pPassive->GetPsvSpd(), pPassive->GetIncSpdCount());

			ImGui::Text("#################################");

			ImGui::Text("Monster");
			ImGui::Text("HP : %d", zombie->characterHp);
		//}
	}
	ImGui::End();
}
