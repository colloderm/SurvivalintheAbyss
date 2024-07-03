#pragma once

#include "Geomatries/Tile/TMap.h"


class TileDemo : public IObject
{
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	TMap* tm = nullptr;
};