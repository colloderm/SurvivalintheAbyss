#pragma once

#include "Geomatries/ShadedTexture.h"

class ShadedDemo : public IObject
{
public:
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	ShadedTexture* st = nullptr;
};