#pragma once

#include "../../../Geomatries/AnimationRect.h"
#include "../../../Manager/CharacterManager.h"

class Skeleton : public CharacterManager
{
public:
	Skeleton(Vector3 position, Vector3 size);
	~Skeleton();

	void Update();
	void Render();

	void Move();
	void Hp(string type, int hp);
	void Attack();
	void Defence();

private:
	AnimationRect* skeleton = nullptr;
	Animator* animator = nullptr;

	int direction = 0;
	bool dmg = false;
};