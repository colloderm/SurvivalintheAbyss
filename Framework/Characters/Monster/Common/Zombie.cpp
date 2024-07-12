#include "Framework.h"
#include "Zombie.h"

Zombie::Zombie(Vector3 position, Vector3 size)
{
	zombie = new AnimationRect(position, size);
	animator = new Animator();

	{
		// 대기
		Texture2D* srcTex = new Texture2D(TexturePath + L"Monster/Zombie/ZombieIdle.png");
		// MonsterIdle
		AnimationClip* Idle = new AnimationClip(L"Idle", srcTex, 19, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		
		animator->AddAnimClip(Idle);
		
		SAFE_DELETE(srcTex);


		// 걷기
		srcTex = new Texture2D(TexturePath + L"Monster/Zombie/ZombieWalk.png");
		// MonsterWalk
		AnimationClip* WalkDR = new AnimationClip(L"WalkDR", srcTex, 4, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* WalkDL = new AnimationClip(L"WalkDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* WalkUR = new AnimationClip(L"WalkUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* WalkUL = new AnimationClip(L"WalkUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });
		
		animator->AddAnimClip(WalkDR);
		animator->AddAnimClip(WalkDL);
		animator->AddAnimClip(WalkUR);
		animator->AddAnimClip(WalkUL);

		SAFE_DELETE(srcTex);


		// 공격
		srcTex = new Texture2D(TexturePath + L"Monster/Zombie/ZombieAttack.png");
		// MonsterAttack
		AnimationClip* AttackDR = new AnimationClip(L"AttackDR", srcTex, 5, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* AttackDL = new AnimationClip(L"AttackDL", srcTex, 5, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* AttackUR = new AnimationClip(L"AttackUR", srcTex, 5, { 0, srcTex->GetHeight() * 0.5f	 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* AttackUL = new AnimationClip(L"AttackUL", srcTex, 5, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(AttackDR);
		animator->AddAnimClip(AttackDL);
		animator->AddAnimClip(AttackUR);
		animator->AddAnimClip(AttackUL);

		SAFE_DELETE(srcTex);


		// 피격
		srcTex = new Texture2D(TexturePath + L"Monster/Zombie/ZombieDmg.png");

		AnimationClip* DmgDR = new AnimationClip(L"DmgDR", srcTex, 4, { 0,						     0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* DmgDL = new AnimationClip(L"DmgDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f	});
		AnimationClip* DmgUR = new AnimationClip(L"DmgUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* DmgUL = new AnimationClip(L"DmgUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(DmgDR);
		animator->AddAnimClip(DmgDL);
		animator->AddAnimClip(DmgUR);
		animator->AddAnimClip(DmgUL);

		SAFE_DELETE(srcTex);


		// 죽음
		srcTex = new Texture2D(TexturePath + L"Monster/Zombie/ZombieDmg.png");

		AnimationClip* Die = new AnimationClip(L"Die", srcTex, 11, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });

		animator->AddAnimClip(Die);

		SAFE_DELETE(srcTex);
	}

	// 기본 애니메이션 설정
	animator->SetCurrentAnimClip(L"Idle");

	// 애니메이터 갈아끼우기
	zombie->SetAnimator(animator);
}

Zombie::~Zombie()
{
	SAFE_DELETE(zombie);
}

void Zombie::Update()
{
	zombie->Update();
}

void Zombie::Render()
{
	zombie->Render();
}

void Zombie::Move()
{
}

void Zombie::Hp(string type, int hp)
{
	if (dmg)
	{
		characterHp -= hp;
	}
}

void Zombie::Attack()
{
}

void Zombie::Defence()
{
}
