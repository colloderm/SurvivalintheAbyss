#pragma once

#include "Geomatries/AnimationRect.h"
#include "Characters/Player.h"
#include "Geomatries/ShadedTexture.h"
#include "Manager/CharacterManager.h"

class PlayerAsset : public IObject
{
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	Player* player = nullptr;
	ShadedTexture* HpPotion = nullptr;

	int potionCount = 1;
};