#pragma once

#include "Framework.h";

enum class State
{
	NONE = -1,
	IDLE,
	WALK,
	ATTACK,
	DMG,
	DIE,
	MAX_VALUE
};

enum class STAT
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
};