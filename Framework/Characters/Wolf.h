#pragma once

#include "../Geomatries/AnimationRect.h"

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

class Wolf
{
public:
	Wolf(Vector3 position, Vector3 size);
	~Wolf();

	void Update();
	void Render();

private:
	AnimationRect* image = nullptr;
	Animator* animator = nullptr;

	State state = State::NONE;

	float stateTime = 0.0f;
};