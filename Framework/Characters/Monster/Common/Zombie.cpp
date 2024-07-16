#include "Framework.h"
#include "Zombie.h"

Zombie::Zombie(Vector3 position, Vector3 size)
{
	zombie = new AnimationRect(position, size);
	animator = new Animator();
	ChaseRect = new Rect(Vector3(zombie->GetPosition().x, zombie->GetPosition().y, 0), Vector3(150, 150, 1));
	DmgRect = new Rect(Vector3(zombie->GetPosition().x, zombie->GetPosition().y, 0), Vector3(60, 40, 1));
	DmgRect->SetColor(Color(1, 1, 1, 1));
	AtkRect = new Rect(Vector3(zombie->GetPosition().x, zombie->GetPosition().y, 0), Vector3(80, 70, 1));
	AtkRect->SetColor(Color(0, 0, 1, 1));

	Target = new Rect(Vector3(360, 150, 0), Vector3(60, 50, 1));
	Target->SetColor(Color(0, 0, 0, 1));

	// 스탯
	characterHp = 10;
	characterAttack = 5;
	characterDefence = 5;
	characterSpeed = 1.0f;
	Gold = 10;

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
	state = State::IDLE;

	// 애니메이터 갈아끼우기
	zombie->SetAnimator(animator);

	startPos = position;
}

Zombie::~Zombie()
{
	SAFE_DELETE(Target);
	SAFE_DELETE(AtkRect);
	SAFE_DELETE(DmgRect);
	SAFE_DELETE(ChaseRect);
	SAFE_DELETE(zombie);
}

void Zombie::Update()
{
	zombie->Update();
	ChaseRect->SetPosition(zombie->GetPosition());
	ChaseRect->Update();
	DmgRect->SetPosition(zombie->GetPosition());
	DmgRect->Update();
	AtkRect->SetPosition(zombie->GetPosition());
	AtkRect->Update();

	if (Mouse::Get()->Press(0x0000))
		Target->SetPosition(Camera::Get()->GetMPosition());
	Target->Update();

	Move();
}

void Zombie::Render()
{
	ChaseRect->Render();
	AtkRect->Render();
	DmgRect->Render();
	zombie->Render();

	Target->Render();
}

void Zombie::Move()
{
	// 추격
	if (BoundingBox::AABB(ChaseRect->GetCollision(), Target->GetCollision()))
	{
		if (BoundingBox::AABB(AtkRect->GetCollision(), Target->GetCollision()))
		{
			state = State::ATTACK;
			stateTime = 0.0f;
			Attack();
		}
		else
		{
			state = State::WALK;
			stateTime = 0.0f;
			//cout << "타겟과 좀비간 거리: (" << movex << ", " << movey << ")" << endl;
			movex = Target->GetPosition().x - zombie->GetPosition().x;
			movey = Target->GetPosition().y - zombie->GetPosition().y;

			if (movex > 0)
				directionx = 1;
			else if (movex < 0)
				directionx = 2;
			else if (movex == 0)
				directionx = 3;

			if (movey > 0)
				directiony = 4;
			else if (movey < 0)
				directiony = 5;
			else if (movey == 0)
				directiony = 6;
		}
	}
	else
	{
		// 추격전까지 패트롤
		if (stateTime >= 1.0f)
		{
			switch (state)
			{
			case State::IDLE:
				state = State::WALK;
				break;
			case State::WALK:
			{
				// 소환위치 확인
				//cout << "최초 위치: (" << startPos.x << ", " << startPos.y << ")" << endl;
				// 이동위치 확인
				//cout << "이동한 위치: (" << zombie->GetPosition().x << ", " << zombie->GetPosition().y << ")" << endl;
				// 이동값 비교
				movex = zombie->GetPosition().x - startPos.x;
				movey = zombie->GetPosition().y - startPos.y;
				// 몬스터 이동
				if (movex <= 50 && movey <= 50)
				{
					directionx = (float)Random::GetRandomInt(1, 2); // 동서
					directiony = (float)Random::GetRandomInt(4, 5); // 북남
				}
				else if (movex >= 50 && movey <= 50)
				{
					directionx = 2;
					directiony = (float)Random::GetRandomInt(4, 5);
				}
				else if (movex < -50 && movey <= 50)
				{
					directionx = 1;
					directiony = (float)Random::GetRandomInt(4, 5);
				}
				else if (movex <= 50 && movey > 50)
				{
					directionx = (float)Random::GetRandomInt(1, 2);
					directiony = 5;
				}
				else if (movex <= 50 && movey < -50)
				{
					directionx = (float)Random::GetRandomInt(1, 2);
					directiony = 4;
				}
				else if (movex >= 50 && movey > 50)
				{
					directionx = 2;
					directiony = 5;
				}
				else if (movex < -50 && movey < -50)
				{
					directionx = 1;
					directiony = 4;
				}

				state = State::IDLE;
			}break;
			}

			stateTime = 0.0f;
		}
		else
			stateTime += Time::Delta();
	}


	switch (state)
	{
	case State::IDLE:
		zombie->GetAnimator()->SetCurrentAnimClip(L"Idle");
		break;
	case State::WALK:
	{
		if (directionx == 1)
		{
			//cout << "동쪽 무빙, 상하체크 " << directiony << endl;
			zombie->MoveAction(1, characterSpeed);
			if (directiony == 4) // 상
			{
				if (directiony != 6)
					zombie->MoveAction(4, characterSpeed);
				zombie->GetAnimator()->SetCurrentAnimClip(L"WalkUR");
			}
			else if (directiony == 5) // 하
			{
				if (directiony != 6)
					zombie->MoveAction(5, characterSpeed);
				zombie->GetAnimator()->SetCurrentAnimClip(L"WalkDR");
			}
		}

		if (directionx == 2)
		{
			//cout << "서쪽 무빙, 상하체크 " << directiony << endl;
			zombie->MoveAction(2, characterSpeed);
			if (directiony == 4) // 상
			{
				if (directiony != 6)
					zombie->MoveAction(4, characterSpeed);
				zombie->GetAnimator()->SetCurrentAnimClip(L"WalkUL");
			}
			else if (directiony == 5) // 하
			{
				if (directiony != 6)
					zombie->MoveAction(5, characterSpeed);
				zombie->GetAnimator()->SetCurrentAnimClip(L"WalkDL");
			}
		}

		if (directionx == 3)
		{
			//cout << "x축 안움직임 " << directiony << endl;
			if (directiony == 4) // 상
			{
				if (directiony != 6)
					zombie->MoveAction(4, characterSpeed);
				zombie->GetAnimator()->SetCurrentAnimClip(L"WalkUL");
			}
			else if (directiony == 5) // 하
			{
				if (directiony != 6)
					zombie->MoveAction(5, characterSpeed);
				zombie->GetAnimator()->SetCurrentAnimClip(L"WalkDL");
			}
		}
	}break;
	}
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
	//cout << directionx << ", " << directiony << endl;
	if ((directionx == 1 && directiony == 5) || (directionx == 1 && directiony == 6))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"AttackDR");
	}
	else if ((directionx == 1 && directiony == 4) || (directionx == 3 && directiony == 4))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"AttackUR");
	}
	else if ((directionx == 2 && directiony == 5) || (directionx == 2 && directiony == 6) || (directionx == 3 && directiony == 5))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"AttackDL");
	}
	else if ((directionx == 2 && directiony == 4))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"AttackUL");
	}
}

void Zombie::Defence()
{
	if ((directionx == 1 && directiony == 5) || (directionx == 1 && directiony == 6))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"DmgDR");
	}
	else if ((directionx == 1 && directiony == 4) || (directionx == 3 && directiony == 4))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"DmgUR");
	}
	else if ((directionx == 2 && directiony == 5) || (directionx == 2 && directiony == 6) || (directionx == 3 && directiony == 5))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"DmgDL");
	}
	else if ((directionx == 2 && directiony == 4))
	{
		zombie->GetAnimator()->SetCurrentAnimClip(L"DmgUL");
	}
}
