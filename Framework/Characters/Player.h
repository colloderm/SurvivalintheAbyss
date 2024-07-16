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

private:
	AnimationRect* player = nullptr;
	Animator* animator = nullptr;
	Rect* ChaseRect = nullptr;
	Rect* DmgRect = nullptr;
	Rect* AtkRect = nullptr;

	// (0 = ��, 1 = ��, 2 = ����)
	//int directionx = 0;
	// (2 = ��, 3 = ��)
	//int directiony = 0;
	int direction = 0;
	int potionCount = 1;
	bool dmg = false;
	float stateTime = 0.0f;
};

