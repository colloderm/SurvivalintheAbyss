#pragma once

#include "../../../Geomatries/AnimationRect.h"
#include "../../../Manager/CharacterManager.h"

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

	int direction = 0;
	bool dmg = false;
};