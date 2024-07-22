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

	// �÷��̾� �ʱⰪ? �Լ�������?
	/*
		�нú��ġüũ �� �Ӽ��� ���߰�,
		��Hp,
		���ݼ�ġ,
		����ġ,
		�̵��ӵ���ġ,

		�������üũ,
		�������ǰ���üũ,
		������� =0,
		(�����ִ¹������üũ,)
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

	// (1 = ��, 2 = ��, 4 = ��, 5 = ��)
	int direction = 0;
	int potionCount = 1;
	float stateTime = 0.0f;
	int hitHp;

	bool isMove = false;
	bool isAttack = false;
	bool isDmg = false;
};

