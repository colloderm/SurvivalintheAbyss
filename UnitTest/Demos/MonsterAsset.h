#pragma once

#include "Geomatries/AnimationRect.h"
#include "Geomatries/ShadedTexture.h"
#include "Manager/CharacterManager.h"
#include "Characters/Monster/Common/Zombie.h"
#include "Characters/Monster/Common/Goblin.h"
#include "Characters/Monster/Common/Slime.h"

#include "Characters/Monster/Boss/Minotaur.h"

#include "Characters/Player.h"


class MonsterAsset : public IObject
{
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	Zombie* zombie = nullptr;
	Goblin* goblin = nullptr;
	Slime* slime = nullptr;

	Minotaur* minotaur = nullptr;

	Rect* Target = nullptr;
};