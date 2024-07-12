#include "Framework.h"
#include "Minotaur.h"

Minotaur::Minotaur(Vector3 position, Vector3 size)
{
	minotaur = new AnimationRect(position, size);
	animator = new Animator();

	{
		// 대기
		Texture2D* srcTex = new Texture2D(TexturePath + L"Boss/Minotaur/MinotaurIdle.png");
		// BossIdle
		AnimationClip* IdleDR = new AnimationClip(L"IdleDR", srcTex, 16, { 0,						   0  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* IdleDL = new AnimationClip(L"IdleDL", srcTex, 16, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* IdleUR = new AnimationClip(L"IdleUR", srcTex, 16, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* IdleUL = new AnimationClip(L"IdleUL", srcTex, 16, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(IdleDR);
		animator->AddAnimClip(IdleDL);
		animator->AddAnimClip(IdleUR);
		animator->AddAnimClip(IdleUL);

		SAFE_DELETE(srcTex);


		// 걷기
		srcTex = new Texture2D(TexturePath + L"Boss/Minotaur/MinotaurWalk.png");
		// BossWalk
		AnimationClip* WalkDR = new AnimationClip(L"WalkDR", srcTex, 6, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* WalkDL = new AnimationClip(L"WalkDL", srcTex, 6, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* WalkUR = new AnimationClip(L"WalkUR", srcTex, 6, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* WalkUL = new AnimationClip(L"WalkUL", srcTex, 6, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(WalkDR);
		animator->AddAnimClip(WalkDL);
		animator->AddAnimClip(WalkUR);
		animator->AddAnimClip(WalkUL);

		SAFE_DELETE(srcTex);


		// 공격
		srcTex = new Texture2D(TexturePath + L"Boss/Minotaur/MinotaurAttack.png");
		// BossAttack
		AnimationClip* AttackDR = new AnimationClip(L"AttackDR", srcTex, 8, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* AttackDL = new AnimationClip(L"AttackDL", srcTex, 8, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* AttackUR = new AnimationClip(L"AttackUR", srcTex, 8, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* AttackUL = new AnimationClip(L"AttackUL", srcTex, 8, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(AttackDR);
		animator->AddAnimClip(AttackDL);
		animator->AddAnimClip(AttackUR);
		animator->AddAnimClip(AttackUL);

		SAFE_DELETE(srcTex);


		// 점프 공격
		srcTex = new Texture2D(TexturePath + L"Boss/Minotaur/MinotaurJump.png");
		// BossJumpAttack
		AnimationClip* JumpAtDR = new AnimationClip(L"JumpAtDR", srcTex, 6, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* JumpAtDL = new AnimationClip(L"JumpAtDL", srcTex, 6, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* JumpAtUR = new AnimationClip(L"JumpAtUR", srcTex, 6, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* JumpAtUL = new AnimationClip(L"JumpAtUL", srcTex, 6, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(JumpAtDR);
		animator->AddAnimClip(JumpAtDL);
		animator->AddAnimClip(JumpAtUR);
		animator->AddAnimClip(JumpAtUL);

		SAFE_DELETE(srcTex);


		// 피격
		srcTex = new Texture2D(TexturePath + L"Boss/Minotaur/MinotaurDmg.png");

		AnimationClip* DmgDR = new AnimationClip(L"DmgDR", srcTex, 4, { 0,						     0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* DmgDL = new AnimationClip(L"DmgDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* DmgUR = new AnimationClip(L"DmgUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* DmgUL = new AnimationClip(L"DmgUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(DmgDR);
		animator->AddAnimClip(DmgDL);
		animator->AddAnimClip(DmgUR);
		animator->AddAnimClip(DmgUL);

		SAFE_DELETE(srcTex);


		// 죽음
		srcTex = new Texture2D(TexturePath + L"Boss/Minotaur/MinotaurDie.png");

		AnimationClip* Die = new AnimationClip(L"Die", srcTex, 15, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(Die);

		SAFE_DELETE(srcTex);
	}

	// 기본 애니메이션 설정
	animator->SetCurrentAnimClip(L"IdleDR");

	// 애니메이터 갈아끼우기
	minotaur->SetAnimator(animator);
}

Minotaur::~Minotaur()
{
	SAFE_DELETE(minotaur);
}

void Minotaur::Update()
{
	minotaur->Update();
}

void Minotaur::Render()
{
	minotaur->Render();
}

void Minotaur::Move()
{
}

void Minotaur::Hp(string type, int hp)
{
	if (dmg)
	{
		characterHp -= hp;
	}
}

void Minotaur::Attack()
{
}

void Minotaur::Defence()
{
}
