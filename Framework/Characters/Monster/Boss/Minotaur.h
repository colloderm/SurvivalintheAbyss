#pragma once

#include "../../../Geomatries/AnimationRect.h"
#include "../../../Manager/CharacterManager.h"

class Minotaur : public CharacterManager
{
public:
	Minotaur(Vector3 position, Vector3 size);
	~Minotaur();

	void Update();
	void Render();

	void Move();
	void Hp(string type, int hp);
	void Attack();
	void Defence();

private:
	AnimationRect* minotaur = nullptr;
	Animator* animator = nullptr;

	int direction = 0;
	bool dmg = false;
};