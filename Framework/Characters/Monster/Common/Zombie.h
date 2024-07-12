#pragma once

#include "../../../Geomatries/AnimationRect.h"
#include "../../../Manager/CharacterManager.h"

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

	int direction = 0;
	bool dmg = false;
};