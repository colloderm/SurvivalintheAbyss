#pragma once

#include "Framework.h";

enum STAT
{
	HP,
	ATK,
	DEF,
	SPD,
	GOLD
};

struct CharacterManager
{
	int characterHp;
	int characterAttack;
	int characterDefence;
	int characterSpeed;
	int Gold;

	void SetStat(int*);
};