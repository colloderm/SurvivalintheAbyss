#pragma once

#include "TextureRect.h"
#include "Utilities/Animator.h"

// enum�� enum class�� ����
// enum ������ ��õǾ� ���� ����, ���� �̸��� ����� �� ����, ������ ������ �ߺ�x
/// 
// enum class�� �ڽŸ��� ������ ����, ���� �̸��� �ٸ����� ����� �� ����, ������ ���������� �ߺ�o
///
//enum class StateUD
//{
//	UP = 0,
//	DOWN
//};
//
//enum class StateLR
//{
//	LEFT = 0,
//	RIGHT
//};

class AnimationRect : public TextureRect
{
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~AnimationRect();

	void Update();
	void Render();

	void SetAnimUV();

	void SetAnimator(Animator* animator) 
	{
		// ������ �ִ°� ����� ���Ƴ����
		SAFE_DELETE(this->animator);
		this->animator = animator; 
	}
	Animator* GetAnimator() { return animator; }

private:
	Animator* animator = nullptr;

	ID3D11SamplerState* sampler = nullptr;
	ID3D11BlendState* blend = nullptr;

	/*StateUD stUD = StateUD::DOWN;
	StateLR stLR = StateLR::RIGHT;*/
};