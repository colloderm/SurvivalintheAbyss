#pragma once

#include "Geomatries/AnimationRect.h"
#include "Manager/CharacterManager.h"
#include "Geomatries/Rect.h"

class Zombie : public CharacterManager
{
public:
	Zombie(Vector3 position, Vector3 size);
	~Zombie();

	void Update();
	void Render();

	void Move();
	void Hp(string type, int hp);
	void Attack();
	void Defence();

private:
	AnimationRect* zombie = nullptr;
	Animator* animator = nullptr;
	Rect* ChaseRect = nullptr;
	Rect* DmgRect = nullptr;
	Rect* AtkRect = nullptr;

	Rect* Target = nullptr;

	State state = State::NONE;

	Vector3 position = Vector3(0, 0, 0);
	Vector3 startPos = Vector3(0, 0, 0);

	int movex = 0;
	int movey = 0;

	// (1 = 동, 2 = 서, 3 = 고정)
	int directionx = 0;
	// (4 = 북, 5 = 남, 6 = 고정)
	int directiony = 0;
	bool dmg = false;

	float stateTime = 0.0f;
};