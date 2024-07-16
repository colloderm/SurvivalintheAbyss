#include "Framework.h"
#include "Goblin.h"

Goblin::Goblin(Vector3 position, Vector3 size)
{
	goblin = new AnimationRect(position, size);
	animator = new Animator();
	ChaseRect = new Rect(Vector3(goblin->GetPosition().x, goblin->GetPosition().y - 2, 0), Vector3(150, 150, 1));
	DmgRect = new Rect(Vector3(goblin->GetPosition().x, goblin->GetPosition().y - 2, 0), Vector3(60, 40, 1));
	DmgRect->SetColor(Color(1, 1, 1, 1));
	AtkRect = new Rect(Vector3(goblin->GetPosition().x, goblin->GetPosition().y, 0), Vector3(80, 70, 1));
	AtkRect->SetColor(Color(0, 0, 1, 1));

	// 스탯
	characterHp = 15;
	characterAttack = 7;
	characterDefence = 7;
	characterSpeed = 1;
	Gold = 15;

	{
		// 대기
		Texture2D* srcTex = new Texture2D(TexturePath + L"Monster/Goblin/GoblinIdle.png");
		// MonsterIdle
		AnimationClip* IdleDR = new AnimationClip(L"IdleDR", srcTex, 16, { 0,						    0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* IdleDL = new AnimationClip(L"IdleDL", srcTex, 16, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f });
		AnimationClip* IdleUR = new AnimationClip(L"IdleUR", srcTex, 16, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* IdleUL = new AnimationClip(L"IdleUL", srcTex, 16, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(IdleDR);
		animator->AddAnimClip(IdleDL);
		animator->AddAnimClip(IdleUR);
		animator->AddAnimClip(IdleUL);

		SAFE_DELETE(srcTex);


		// 걷기
		srcTex = new Texture2D(TexturePath + L"Monster/Goblin/GoblinWalk.png");
		// MonsterWalk
		AnimationClip* WalkDR = new AnimationClip(L"WalkDR", srcTex, 4, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* WalkDL = new AnimationClip(L"WalkDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f });
		AnimationClip* WalkUR = new AnimationClip(L"WalkUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* WalkUL = new AnimationClip(L"WalkUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(WalkDR);
		animator->AddAnimClip(WalkDL);
		animator->AddAnimClip(WalkUR);
		animator->AddAnimClip(WalkUL);

		SAFE_DELETE(srcTex);


		// 공격
		srcTex = new Texture2D(TexturePath + L"Monster/Goblin/GoblinAttack.png");
		// MonsterAttack
		AnimationClip* AttackDR = new AnimationClip(L"AttackDR", srcTex, 4, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* AttackDL = new AnimationClip(L"AttackDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f });
		AnimationClip* AttackUR = new AnimationClip(L"AttackUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* AttackUL = new AnimationClip(L"AttackUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(AttackDR);
		animator->AddAnimClip(AttackDL);
		animator->AddAnimClip(AttackUR);
		animator->AddAnimClip(AttackUL);

		SAFE_DELETE(srcTex);


		// 피격
		srcTex = new Texture2D(TexturePath + L"Monster/Goblin/GoblinDmg.png");

		AnimationClip* DmgDR = new AnimationClip(L"DmgDR", srcTex, 4, { 0,						     0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* DmgDL = new AnimationClip(L"DmgDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f });
		AnimationClip* DmgUR = new AnimationClip(L"DmgUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* DmgUL = new AnimationClip(L"DmgUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(DmgDR);
		animator->AddAnimClip(DmgDL);
		animator->AddAnimClip(DmgUR);
		animator->AddAnimClip(DmgUL);

		SAFE_DELETE(srcTex);


		// 죽음
		srcTex = new Texture2D(TexturePath + L"Monster/Goblin/GoblinSpinDie.png");

		AnimationClip* Die = new AnimationClip(L"Die", srcTex, 12, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(Die);

		SAFE_DELETE(srcTex);
	}

	// 기본 애니메이션 설정
	animator->SetCurrentAnimClip(L"IdleDR");
	state = State::IDLE;

	// 애니메이터 갈아끼우기
	goblin->SetAnimator(animator);

	startPos = position;
}

Goblin::~Goblin()
{
	SAFE_DELETE(AtkRect);
	SAFE_DELETE(DmgRect);
	SAFE_DELETE(ChaseRect);
	SAFE_DELETE(goblin);
}

void Goblin::Update()
{
	goblin->Update();
	ChaseRect->SetPosition(goblin->GetPosition());
	ChaseRect->Update();
	DmgRect->SetPosition(goblin->GetPosition());
	DmgRect->Update();
	AtkRect->SetPosition(goblin->GetPosition());
	AtkRect->Update();
}

void Goblin::Render()
{
	ChaseRect->Render();
	AtkRect->Render();
	DmgRect->Render();
	goblin->Render();
}

void Goblin::Move()
{
}

void Goblin::Hp(string type, int hp)
{
	if (dmg)
	{
		characterHp -= hp;
	}
}

void Goblin::Attack()
{
}

void Goblin::Defence()
{
}
