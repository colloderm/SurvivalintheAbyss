#pragma once

#include "Geomatries/Tile/TMap.h"
#include "Geomatries/TextureRect.h"
#include "Geomatries/ShadedTexture.h"

class StartStage : public IObject
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
	TMap* tm2 = nullptr;
	TMap* tm3 = nullptr;

	TextureRect* BlacksmithShop = nullptr;
	TextureRect* SorceryShop = nullptr;
	TextureRect* ItemShop = nullptr;

	wstring woodPath = L"";
	Vector3 woodSize;
	TextureRect* TriangleTree = nullptr;
	TextureRect* BasicTree = nullptr;
	TextureRect* DoubleTree = nullptr;
	TextureRect* LongTree = nullptr;
	vector<TextureRect*> others;
};