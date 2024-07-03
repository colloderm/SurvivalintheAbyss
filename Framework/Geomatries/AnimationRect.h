#pragma once

#include "TextureRect.h"
#include "Utilities/Animator.h"

// enum과 enum class의 차이
// enum 공간이 명시되어 있지 않음, 같은 이름을 사용할 수 없음, 접근이 쉽지만 중복x
/// 
// enum class는 자신만의 공간이 있음, 같은 이름을 다른곳에 사용할 수 있음, 접근이 복잡하지만 중복o
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
		// 가지고 있는걸 지우고 갈아끼우기
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