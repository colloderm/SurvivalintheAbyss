#include "Framework.h"
#include "Slime.h"

Slime::Slime(Vector3 position, Vector3 size)
{
	slime = new AnimationRect(position, size);
	animator = new Animator();
	ChaseRect = new Rect(Vector3(slime->GetPosition().x, slime->GetPosition().y - 2, 0), Vector3(150, 150, 1));
	DmgRect = new Rect(Vector3(slime->GetPosition().x, slime->GetPosition().y - 2, 0), Vector3(60, 40, 1));
	DmgRect->SetColor(Color(1, 1, 1, 1));
	AtkRect = new Rect(Vector3(slime->GetPosition().x, slime->GetPosition().y, 0), Vector3(80, 70, 1));
	AtkRect->SetColor(Color(0, 0, 1, 1));

	// 스탯
	characterHp = 15;
	characterAttack = 7;
	characterDefence = 7;
	characterSpeed = 1;
	Gold = 20;

	{
		// 대기
		Texture2D* srcTex = new Texture2D(TexturePath + L"Monster/Slime/SlimeGreenIdle.png");
		// MonsterIdle
		AnimationClip* IdleDR = new AnimationClip(L"IdleDR", srcTex, 8, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* IdleDL = new AnimationClip(L"IdleDL", srcTex, 8, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* IdleUR = new AnimationClip(L"IdleUR", srcTex, 8, { 0, srcTex->GetHeight() * 0.5f	 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* IdleUL = new AnimationClip(L"IdleUL", srcTex, 8, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(IdleDR);
		animator->AddAnimClip(IdleDL);
		animator->AddAnimClip(IdleUR);
		animator->AddAnimClip(IdleUL);

		SAFE_DELETE(srcTex);


		// 공격
		srcTex = new Texture2D(TexturePath + L"Monster/Slime/SlimeGreenJumpAttack.png");
		// MonsterAttack
		AnimationClip* AttackDR = new AnimationClip(L"AttackDR", srcTex, 4, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* AttackDL = new AnimationClip(L"AttackDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* AttackUR = new AnimationClip(L"AttackUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f	 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* AttackUL = new AnimationClip(L"AttackUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(AttackDR);
		animator->AddAnimClip(AttackDL);
		animator->AddAnimClip(AttackUR);
		animator->AddAnimClip(AttackUL);

		SAFE_DELETE(srcTex);


		// 피격
		srcTex = new Texture2D(TexturePath + L"Monster/Slime/SlimeGreenDmg.png");

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
		srcTex = new Texture2D(TexturePath + L"Monster/Slime/SlimeGreenDie.png");

		AnimationClip* Die = new AnimationClip(L"Die", srcTex, 9, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(Die);

		SAFE_DELETE(srcTex);
	}

	// 기본 애니메이션 설정
	animator->SetCurrentAnimClip(L"IdleDR");
	state = State::IDLE;

	// 애니메이터 갈아끼우기
	slime->SetAnimator(animator);

	startPos = position;
}

Slime::~Slime()
{
	SAFE_DELETE(AtkRect);
	SAFE_DELETE(DmgRect);
	SAFE_DELETE(ChaseRect);
	SAFE_DELETE(slime);
}

void Slime::Update()
{
	slime->Update();
	ChaseRect->SetPosition(slime->GetPosition());
	ChaseRect->Update();
	DmgRect->SetPosition(slime->GetPosition());
	DmgRect->Update();
	AtkRect->SetPosition(slime->GetPosition());
	AtkRect->Update();
}

void Slime::Render()
{
	ChaseRect->Render();
	AtkRect->Render();
	DmgRect->Render();
	slime->Render();
}

void Slime::Move()
{
}

void Slime::Hp(string type, int hp)
{
	if (dmg)
	{
		characterHp -= hp;
	}
}

void Slime::Attack()
{
}

void Slime::Defence()
{
}
