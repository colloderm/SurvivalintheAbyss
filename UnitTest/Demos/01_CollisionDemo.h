#pragma once

#include "Geomatries/Rect.h"

class CollisionDemo : public IObject
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
	Rect* player = nullptr;
	Rect* other = nullptr;

	vector<Rect*> others;
	UINT oc = 10;

};