#include "stdafx.h"
#include "MonsterAsset.h"

void MonsterAsset::Init()
{
	zombie = new Zombie({ 200, 200, 0 }, { 200, 200, 1 });
	skeleton = new Skeleton({ 300, 200, 0 }, { 200, 200, 1 });
	slime = new Slime({ 400, 200, 0 }, { 200, 200, 1 });

	// Common
	int zombieStat[] = { 10, 5, 5, 1, 10 };
	zombie->SetStat(zombieStat);

	int skeletonStat[] = { 10, 5, 5, 1, 15 };
	skeleton->SetStat(skeletonStat);

	int slimeStat[] = { 15, 7, 7, 1, 20 };
	slime->SetStat(slimeStat);

	// Boss
	minotaur = new Minotaur({ 900, 200, 0 }, { 300, 300, 1 });

	int minotaurStat[] = { 100, 15, 15, 2, 200 };
	minotaur->SetStat(minotaurStat);
}

void MonsterAsset::Destroy()
{
	SAFE_DELETE(minotaur);
	SAFE_DELETE(slime);
	SAFE_DELETE(skeleton);
	SAFE_DELETE(zombie);
}

void MonsterAsset::Update()
{
	zombie->Move();
	zombie->Attack();
	zombie->Defence();

	skeleton->Move();
	skeleton->Attack();
	skeleton->Defence();

	slime->Move();
	slime->Attack();
	slime->Defence();

	minotaur->Move();
	minotaur->Attack();
	minotaur->Defence();

	zombie->Update();
	skeleton->Update();
	slime->Update();

	minotaur->Update();
}

void MonsterAsset::Render()
{
	zombie->Render();
	skeleton->Render();
	slime->Render();

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
		ImGui::Text("HP : %d\t  HP : %d\t  HP : %d", zombie->characterHp, skeleton->characterHp, slime->characterHp);
		ImGui::Text("ATK : %d\t  ATK : %d\t  ATK : %d", zombie->characterAttack, skeleton->characterAttack, slime->characterAttack);
		ImGui::Text("DEF : %d\t  DEF : %d\t  DEF : %d", zombie->characterDefence, skeleton->characterDefence, slime->characterDefence);
		ImGui::Text("SPD : %d\t  SPD : %d\t  SPD : %d", zombie->characterSpeed, skeleton->characterSpeed, slime->characterSpeed);
		ImGui::Text("Gold : %d\tGold : %d\tGold : %d", zombie->Gold, skeleton->Gold, slime->Gold);

		ImGui::Text("#################################");

		ImGui::Text("[Boss]");
		ImGui::Text("Minotaur");
		ImGui::Text("HP : %d", minotaur->characterHp);
		ImGui::Text("ATK : %d", minotaur->characterAttack);
		ImGui::Text("DEF : %d", minotaur->characterDefence);
		ImGui::Text("SPD : %d", minotaur->characterSpeed);
		ImGui::Text("Gold : %d", minotaur->Gold);
	}
	ImGui::End();
}
