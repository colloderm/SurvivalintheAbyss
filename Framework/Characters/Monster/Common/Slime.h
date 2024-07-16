#pragma once

#include "Geomatries/AnimationRect.h"
#include "Manager/CharacterManager.h"
#include "Geomatries/Rect.h"

class Slime : public CharacterManager
{
public:
	Slime(Vector3 position, Vector3 size);
	~Slime();

	void Update();
	void Render();

	void Move();
	void Hp(string type, int hp);
	void Attack();
	void Defence();

private:
	AnimationRect* slime = nullptr;
	Animator* animator = nullptr;
	Rect* ChaseRect = nullptr;
	Rect* DmgRect = nullptr;
	Rect* AtkRect = nullptr;

	State state = State::NONE;

	Vector3 position = Vector3(0, 0, 0);
	Vector3 startPos = Vector3(0, 0, 0);

	int direction = 0;
	bool dmg = false;
};