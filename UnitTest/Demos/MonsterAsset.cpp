#include "stdafx.h"
#include "MonsterAsset.h"

void MonsterAsset::Init()
{
	// Common
	zombie = new Zombie({ 150, 150, 0 }, { 200, 200, 1 });
	goblin = new Goblin({ 250, 250, 0 }, { 200, 200, 1 });
	slime = new Slime({ 400, 400, 0 }, { 200, 200, 1 });

	// Boss
	minotaur = new Minotaur({ 900, 200, 0 }, { 300, 300, 1 });
}

void MonsterAsset::Destroy()
{
	SAFE_DELETE(minotaur);
	SAFE_DELETE(slime);
	SAFE_DELETE(goblin);
	SAFE_DELETE(zombie);
}

void MonsterAsset::Update()
{

	goblin->Move();
	goblin->Attack();
	goblin->Defence();

	slime->Move();
	slime->Attack();
	slime->Defence();

	minotaur->Move();
	minotaur->Attack();
	minotaur->Defence();

	zombie->Update();
	goblin->Update();
	slime->Update();

	minotaur->Update();
}

void MonsterAsset::Render()
{
	zombie->Render();
	//goblin->Render();
	//slime->Render();

	minotaur->Render();
}

void MonsterAsset::PostRender()
{
}

void MonsterAsset::GUI()
{
	ImGui::Begin("SurvivalintheAbyss");
	{
		ImGui::Text("[common]");
		ImGui::Text("Zombie\t   Skeleton\t Slime");
		ImGui::Text("HP : %d\t  HP : %d\t  HP : %d", zombie->characterHp, goblin->characterHp, slime->characterHp);
		ImGui::Text("ATK : %d\t  ATK : %d\t  ATK : %d", zombie->characterAttack, goblin->characterAttack, slime->characterAttack);
		ImGui::Text("DEF : %d\t  DEF : %d\t  DEF : %d", zombie->characterDefence, goblin->characterDefence, slime->characterDefence);
		ImGui::Text("SPD : %.1f\tSPD : %.1f\tSPD : %.1f", zombie->characterSpeed, goblin->characterSpeed, slime->characterSpeed);
		ImGui::Text("Gold : %d\tGold : %d\tGold : %d", zombie->Gold, goblin->Gold, slime->Gold);

		ImGui::Text("#################################");

		ImGui::Text("[Boss]");
		ImGui::Text("Minotaur");
		ImGui::Text("HP : %d", minotaur->characterHp);
		ImGui::Text("ATK : %d", minotaur->characterAttack);
		ImGui::Text("DEF : %d", minotaur->characterDefence);
		ImGui::Text("SPD : %.1f", minotaur->characterSpeed);
		ImGui::Text("Gold : %d", minotaur->Gold);
	}
	ImGui::End();
}
