#pragma once

#include "Geomatries/AnimationRect.h"
#include "Manager/CharacterManager.h"
#include "Geomatries/Rect.h"
#include "Manager/PlayerPassive.h"

class Player : public CharacterManager
{
public:
	Player(Vector3 position, Vector3 size);
	~Player();

	void Update();
	void Render();
	
	void Move();
	void Hp(string type, int hp);
	void Attack();
	void Defence();
	void Inventory();
	void Interaction();

	// 플레이어 초기값? 함수설정값?
	/*
		패시브수치체크 각 속성에 값추가,
		총Hp,
		공격수치,
		방어수치,
		이동속도수치,

		현재장비체크,
		현재포션개수체크,
		소지골드 =0,
		(보고있는방향수시체크,)
	*/

	Rect* GetDmgRect() { return DmgRect; }

	void SetPosition(Vector3 position) { player->SetPosition(position); }
	void SetTarget(Rect* target) { this->Monster = target; }

	void SetPassive(PlayerPassive* Psv);

private:
	AnimationRect* player = nullptr;
	Animator* animator = nullptr;
	Rect* DmgRect = nullptr;
	Rect* AtkRangeRect = nullptr;
	Rect* AtkRect = nullptr;

	Rect* Monster = nullptr;

	// (1 = 동, 2 = 서, 4 = 북, 5 = 남)
	int direction = 0;
	int potionCount = 1;
	float stateTime = 0.0f;
	int hitHp;

	bool isMove = false;
	bool isAttack = false;
	bool isDmg = false;

	bool moveD = false;
	bool moveR = false;
};

