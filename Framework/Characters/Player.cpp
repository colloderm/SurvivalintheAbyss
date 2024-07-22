#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
{
	player = new AnimationRect(position, size);
	animator = new Animator();
	DmgRect = new Rect(Vector3(player->GetPosition().x, player->GetPosition().y, 0), Vector3(60, 40, 1));
	DmgRect->SetColor(Color(1, 1, 1, 1));
	AtkRangeRect = new Rect(Vector3(player->GetPosition().x, player->GetPosition().y, 0), Vector3(80, 70, 1));
	AtkRangeRect->SetColor(Color(0, 0, 1, 1));
	AtkRect = new Rect(Vector3(player->GetPosition().x, player->GetPosition().y, 0), Vector3(70, 70, 1));
	AtkRect->SetColor(Color(1, 0, 1, 1));

	Monster = new Rect(Vector3(360, 150, 0), Vector3(60, 50, 1));
	Monster->SetColor(Color(0, 0, 0, 1));

	// 스탯
	characterHp = 20;
	characterAttack = 10;
	characterDefence = 10;
	characterSpeed = 10.0f;
	Gold = 0;

	{
		// 대기
		Texture2D* srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerIdleBT.png");
		// PlayerIdle
		AnimationClip* IdleBT = new AnimationClip(L"IdleBT", srcTex, 4, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(IdleBT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerIdleUP.png");
		AnimationClip* IdleUP = new AnimationClip(L"IdleUP", srcTex, 4, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(IdleUP);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerIdleRT.png");
		AnimationClip* IdleRT = new AnimationClip(L"IdleRT", srcTex, 4, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(IdleRT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerIdleLT.png");
		AnimationClip* IdleLT = new AnimationClip(L"IdleLT", srcTex, 4, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(IdleLT);
		SAFE_DELETE(srcTex);


		// 걷기
		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerRunBT.png");
		// PlayerRun
		AnimationClip* RunBT = new AnimationClip(L"RunBT", srcTex, 6, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(RunBT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerRunUP.png");
		AnimationClip* RunUP = new AnimationClip(L"RunUP", srcTex, 6, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(RunUP);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerRunRT.png");
		AnimationClip* RunRT = new AnimationClip(L"RunRT", srcTex, 6, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(RunRT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerRunLT.png");
		AnimationClip* RunLT = new AnimationClip(L"RunLT", srcTex, 6, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(RunLT);
		SAFE_DELETE(srcTex);

		// 공격
		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerAttackBT.png");
		// PlayerAttack
		AnimationClip* AttackBT = new AnimationClip(L"AttackBT", srcTex, 7, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(AttackBT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerAttackUP.png");
		AnimationClip* AttackUP = new AnimationClip(L"AttackUP", srcTex, 7, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(AttackUP);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerAttackRT.png");
		AnimationClip* AttackRT = new AnimationClip(L"AttackRT", srcTex, 7, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(AttackRT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerAttackLT.png");
		AnimationClip* AttackLT = new AnimationClip(L"AttackLT", srcTex, 7, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(AttackLT);
		SAFE_DELETE(srcTex);


		// 죽음
		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerDieBT.png");
		// PlayerDie
		AnimationClip* DieBT = new AnimationClip(L"DieBT", srcTex, 9, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(DieBT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerDieUP.png");
		AnimationClip* DieUP = new AnimationClip(L"DieUP", srcTex, 9, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(DieUP);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerDieRT.png");
		AnimationClip* DieRT = new AnimationClip(L"DieRT", srcTex, 9, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(DieRT);
		SAFE_DELETE(srcTex);

		srcTex = new Texture2D(TexturePath + L"Player/swordman/PlayerDieLT.png");
		AnimationClip* DieLT = new AnimationClip(L"DieLT", srcTex, 9, { 0, 0 }, { srcTex->GetWidth(), srcTex->GetHeight() });
		animator->AddAnimClip(DieLT);
		SAFE_DELETE(srcTex);
	}

	// 기본 애니메이션 설정
	animator->SetCurrentAnimClip(L"IdleBT");

	// 애니메이터 갈아끼우기
	player->SetAnimator(animator);
}

Player::~Player()
{
	SAFE_DELETE(AtkRect);
	SAFE_DELETE(AtkRangeRect);
	SAFE_DELETE(DmgRect);
	SAFE_DELETE(player);
}

void Player::Update()
{
	player->Update();
	DmgRect->SetPosition(player->GetPosition());
	DmgRect->Update();
	AtkRangeRect->SetPosition(player->GetPosition());
	AtkRangeRect->Update();

	switch (direction)
	{
	case 1: // 동
		AtkRect->SetPosition({ player->GetPosition().x + 100, player->GetPosition().y, 1 });
		break;
	case 2: // 서
		AtkRect->SetPosition({ player->GetPosition().x - 100, player->GetPosition().y, 1 });
		break;
	case 4: // 북
		AtkRect->SetPosition({ player->GetPosition().x, player->GetPosition().y + 150, 1 });
		break;
	case 5: // 남
		AtkRect->SetPosition({ player->GetPosition().x, player->GetPosition().y - 150, 1 });
		break;
	}
	AtkRect->Update();
}

void Player::Render()
{
	AtkRangeRect->Render();
	if (isAttack)
		AtkRect->Render();
	DmgRect->Render();
	player->Render();
}

void Player::Move()
{
	// 대기 (기본상태 & 걷기 후 멈춤상태)
	if (Keyboard::Get()->Down('D') || Keyboard::Get()->Up('D') || (Keyboard::Get()->Up(0x0001) && direction == 1))
	{
		isAttack = false;
		player->GetAnimator()->SetCurrentAnimClip(L"IdleRT");
		direction = 1;
	}
	else if (Keyboard::Get()->Down('A') || Keyboard::Get()->Up('A') || (Keyboard::Get()->Up(0x0001) && direction == 2))
	{
		isAttack = false;
		player->GetAnimator()->SetCurrentAnimClip(L"IdleLT");
		direction = 2;
	}
	else if (Keyboard::Get()->Down('W') || Keyboard::Get()->Up('W') || (Keyboard::Get()->Up(0x0001) && direction == 4))
	{
		isAttack = false;
		player->GetAnimator()->SetCurrentAnimClip(L"IdleUP");
		direction = 4;
	}
	else if (Keyboard::Get()->Down('S') || Keyboard::Get()->Up('S') || (Keyboard::Get()->Up(0x0001) && direction == 5))
	{
		isAttack = false;
		player->GetAnimator()->SetCurrentAnimClip(L"IdleBT");
		direction = 5;
	}

	if (isAttack == false)
	{
		// 걷기
		if (Keyboard::Get()->Press('S') || Keyboard::Get()->Press('s'))
		{
			player->GetAnimator()->SetCurrentAnimClip(L"RunBT");
			player->MoveAction(direction, characterSpeed);
		}
		else if (Keyboard::Get()->Press('W') || Keyboard::Get()->Press('w'))
		{
			player->GetAnimator()->SetCurrentAnimClip(L"RunUP");
			player->MoveAction(direction, characterSpeed);
		}
		else if (Keyboard::Get()->Press('A') || Keyboard::Get()->Press('a'))
		{
			player->GetAnimator()->SetCurrentAnimClip(L"RunLT");
			player->MoveAction(direction, characterSpeed);
		}
		else if (Keyboard::Get()->Press('D') || Keyboard::Get()->Press('d'))
		{
			player->GetAnimator()->SetCurrentAnimClip(L"RunRT");
			player->MoveAction(direction, characterSpeed);
		}
	}
}

void Player::Hp(string type,  int hp)
{
	if (type == "passive")
	{
		// 1. 기본 Hp에 패시브의 hp증가값 적용
		characterHp += hp;
	}
	else if (type == "potion")
	{
		// 2. 포션사용 후 현재 체력에 + 적용
		characterHp += 50;
	}
	else if (type == "dmg")
	{
		// 3. 피격 시 현재 체력에 - 적용
		characterHp -= hp;
	}
}

void Player::Attack()
{
	// 공격
	if (Keyboard::Get()->Press(0x0001))
	{
		isAttack = true;
		switch (direction)
		{
		case 5:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackBT");
			break;
		case 4:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackUP");
			break;
		case 2:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackLT");
			break;
		case 1:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackRT");
			break;
		}
	}

	if (BoundingBox::AABB(AtkRect->GetCollision(), Monster->GetCollision()))
	{
		//Hp("dmg", characterAttack);
		isDmg = true;
	}
	else
		isDmg = false;
}

void Player::Defence()
{
	// 피격
	if (isDmg && direction == 0)
	{
		hitHp = characterAttack - characterDefence; // 계산식 = 몬스터의 공격력 - 플레이어의 방어력;
		Hp("dmg", hitHp);
		// 보고있는 방향의 위치에서 뒤로 조금(0.5cm?) 움직이도록 설정
	}

	// 사망
	if (isDmg && characterHp == 0)
	{
		switch (direction)
		{
		case 5:
			player->GetAnimator()->SetCurrentAnimClip(L"DieBT");
			break;
		case 4:
			player->GetAnimator()->SetCurrentAnimClip(L"DieUP");
			break;
		case 2:
			player->GetAnimator()->SetCurrentAnimClip(L"DieLT");
			break;
		case 1:
			player->GetAnimator()->SetCurrentAnimClip(L"DieRT");
			break;
		}
	}
}

void Player::Inventory()
{
	// 포션
	if (Keyboard::Get()->Press('Q'))
	{
		if (potionCount != 0)
		{
			potionCount--;
		}
	}

	// 장비
}

void Player::Interaction()
{
	// 상호작용?
	// 패시브 관련

	// 장비 교체?
}

void Player::SetPassive(PlayerPassive* Psv)
{
	this->characterHp += Psv->GetPsvHp();
	this->characterAttack += Psv->GetPsvAtk();
	this->characterDefence += Psv->GetPsvDef();
	this->characterSpeed += Psv->GetPsvSpd();
}
