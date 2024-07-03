#pragma once

#include "Geomatries/Rect.h"

class RectDemo : public IObject
{
public:
	// IObject��(��) ���� ��ӵ�
	virtual void Init() override;			// ������
	virtual void Destroy() override;		// �Ҹ���
	virtual void Update() override;			// ������Ʈ
	virtual void Render() override;			// ����
	virtual void PostRender() override;		// ��ó�� // 2D���� �� �Ⱦ�
	virtual void GUI() override;			// GUI�ڵ� �ִ� ��

private:
	Rect* r = nullptr;
};