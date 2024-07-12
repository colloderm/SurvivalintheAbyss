#include "Framework.h"
#include "Slime.h"

Slime::Slime(Vector3 position, Vector3 size)
{
	slime = new AnimationRect(position, size);
	animator = new Animator();

	{
		// ���
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


		// ����
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


		// �ǰ�
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


		// ����
		srcTex = new Texture2D(TexturePath + L"Monster/Slime/SlimeGreenDie.png");

		AnimationClip* Die = new AnimationClip(L"Die", srcTex, 9, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(Die);

		SAFE_DELETE(srcTex);
	}

	// �⺻ �ִϸ��̼� ����
	animator->SetCurrentAnimClip(L"IdleDR");

	// �ִϸ����� ���Ƴ����
	slime->SetAnimator(animator);
}

Slime::~Slime()
{
	SAFE_DELETE(slime);
}

void Slime::Update()
{
	slime->Update();
}

void Slime::Render()
{
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