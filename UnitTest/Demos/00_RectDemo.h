#pragma once

#include "Geomatries/Rect.h"

class RectDemo : public IObject
{
public:
	// IObject을(를) 통해 상속됨
	virtual void Init() override;			// 생성자
	virtual void Destroy() override;		// 소멸자
	virtual void Update() override;			// 업데이트
	virtual void Render() override;			// 랜더
	virtual void PostRender() override;		// 후처리 // 2D에선 잘 안씀
	virtual void GUI() override;			// GUI코드 넣는 곳

private:
	Rect* r = nullptr;
};