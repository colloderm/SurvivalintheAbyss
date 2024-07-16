#pragma once

#include "Geomatries/AnimationRect.h"
#include "Manager/CharacterManager.h"
#include "Geomatries/Rect.h"

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

private:
	AnimationRect* player = nullptr;
	Animator* animator = nullptr;
	Rect* ChaseRect = nullptr;
	Rect* DmgRect = nullptr;
	Rect* AtkRect = nullptr;

	// (0 = 동, 1 = 서, 2 = 고정)
	//int directionx = 0;
	// (2 = 북, 3 = 남)
	//int directiony = 0;
	int direction = 0;
	int potionCount = 1;
	bool dmg = false;
	float stateTime = 0.0f;
};

