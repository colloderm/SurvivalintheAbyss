#pragma once

#include "Geomatries/AnimationRect.h"
#include "Characters/Wolf.h"
#include "00_RectDemo.h"
#include "01_CollisionDemo.h"
#include "02_TextureDemo.h"

class AnimDemo : public IObject
{
public:
	// IObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	AnimationRect* ar = nullptr;
	Wolf* wolf = nullptr;
	Wolf* wolf2 = nullptr;

	RectDemo* rd = nullptr;
	CollisionDemo* cd = nullptr;
	TextureDemo* td = nullptr;

	int demoCount = 0;
};