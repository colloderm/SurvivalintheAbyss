#include "Framework.h"
#include "Wolf.h"

Wolf::Wolf(Vector3 position, Vector3 size)
{
	image = new AnimationRect(position, size);
	animator = new Animator();

	{
		// 걷기
		Texture2D* srcTex = new Texture2D(TexturePath + L"Wolf/WolfWalk.png");

		AnimationClip* WalkDR = new AnimationClip(L"WalkDR", srcTex, 4, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* WalkDL = new AnimationClip(L"WalkDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* WalkUR = new AnimationClip(L"WalkUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f	 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* WalkUL = new AnimationClip(L"WalkUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight()		  });

		animator->AddAnimClip(WalkDR);
		animator->AddAnimClip(WalkDL);
		animator->AddAnimClip(WalkUR);
		animator->AddAnimClip(WalkUL);

		SAFE_DELETE(srcTex);

		// 대기
		srcTex = new Texture2D(TexturePath + L"Wolf/WolfIdle.png");

		AnimationClip* IdleDR = new AnimationClip(L"IdleDR", srcTex, 12, { 0,						    0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* IdleDL = new AnimationClip(L"IdleDL", srcTex, 12, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* IdleUR = new AnimationClip(L"IdleUR", srcTex, 12, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* IdleUL = new AnimationClip(L"IdleUL", srcTex, 12, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight()		   });

		animator->AddAnimClip(IdleDR);
		animator->AddAnimClip(IdleDL);
		animator->AddAnimClip(IdleUR);
		animator->AddAnimClip(IdleUL);

		SAFE_DELETE(srcTex);

		// 공격
		srcTex = new Texture2D(TexturePath + L"Wolf/WolfAttack.png");

		AnimationClip* AttackDR = new AnimationClip(L"AttackDR", srcTex, 4, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* AttackDL = new AnimationClip(L"AttackDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* AttackUR = new AnimationClip(L"AttackUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* AttackUL = new AnimationClip(L"AttackUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight()		  });

		animator->AddAnimClip(AttackDR);
		animator->AddAnimClip(AttackDL);
		animator->AddAnimClip(AttackUR);
		animator->AddAnimClip(AttackUL);

		SAFE_DELETE(srcTex);

		// 피격
		srcTex = new Texture2D(TexturePath + L"Wolf/WolfDmg.png");

		AnimationClip* DmgDR = new AnimationClip(L"DmgDR", srcTex, 4, { 0,						     0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* DmgDL = new AnimationClip(L"DmgDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* DmgUR = new AnimationClip(L"DmgUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* DmgUL = new AnimationClip(L"DmgUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight()			});

		animator->AddAnimClip(DmgDR);
		animator->AddAnimClip(DmgDL);
		animator->AddAnimClip(DmgUR);
		animator->AddAnimClip(DmgUL);

		SAFE_DELETE(srcTex);

		// 죽음
		srcTex = new Texture2D(TexturePath + L"Wolf/WolfDie.png");

		AnimationClip* Die = new AnimationClip(L"Die", srcTex, 9, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(Die);

		SAFE_DELETE(srcTex);
	}

	// 기본 애니메이션 설정
	animator->SetCurrentAnimClip(L"IdleDR");
	state = State::IDLE;

	// 애니메이터 갈아끼우기
	image->SetAnimator(animator);
}

Wolf::~Wolf()
{
	SAFE_DELETE(image);
}

void Wolf::Update()
{
	if (stateTime >= 3.0f)
	{
		switch (state)
		{
		case State::IDLE:
			state = State::WALK;
			break;
		case State::WALK:
			state = State::ATTACK;
			break;
		case State::ATTACK:
			state = State::DMG;
			break;
		case State::DMG:
			state = State::DIE;
			break;
		case State::DIE:
			state = State::IDLE;
			break;
		}

		stateTime = 0.0f;
	}
	else stateTime += Time::Delta();

	switch (state)
	{
	case State::IDLE:
	{
		image->GetAnimator()->SetCurrentAnimClip(L"IdleDR");
	}break;
	case State::WALK:
	{
		image->GetAnimator()->SetCurrentAnimClip(L"WalkDR");
	}break;
	case State::ATTACK:
	{
		image->GetAnimator()->SetCurrentAnimClip(L"AttackDR");
	}break;
	case State::DMG:
	{
		image->GetAnimator()->SetCurrentAnimClip(L"DmgDR");
	}break;
	case State::DIE:
	{
		image->GetAnimator()->SetCurrentAnimClip(L"Die");
	}break;
	}

	image->Update();
}

void Wolf::Render()
{
	image->Render();
}
