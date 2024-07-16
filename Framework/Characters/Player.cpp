#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
{
	player = new AnimationRect(position, size);
	animator = new Animator();

	// ����
	characterHp = 20;
	characterAttack = 10;
	characterDefence = 10;
	characterSpeed = 1.0;
	Gold = 0;

	{
		// ���
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


		// �ȱ�
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

		// ����
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


		// ����
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

	// �⺻ �ִϸ��̼� ����
	animator->SetCurrentAnimClip(L"IdleBT");

	// �ִϸ����� ���Ƴ����
	player->SetAnimator(animator);
}

Player::~Player()
{
	SAFE_DELETE(player);
}

void Player::Update()
{
	player->Update();
}

void Player::Render()
{
	player->Render();
}

void Player::Move()
{
	// ��� (�⺻���� & �ȱ� �� �������)
	if (Keyboard::Get()->Down('S') || Keyboard::Get()->Up('S') || (Keyboard::Get()->Up(0x0001) && direction == 0))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"IdleBT");
		direction = 0;
	}
	else if (Keyboard::Get()->Down('W') || Keyboard::Get()->Up('W') || (Keyboard::Get()->Up(0x0001) && direction == 1))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"IdleUP");
		direction = 1;
	}
	else if (Keyboard::Get()->Down('A') || Keyboard::Get()->Up('A') || (Keyboard::Get()->Up(0x0001) && direction == 2))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"IdleLT");
		direction = 2;
	}
	else if (Keyboard::Get()->Down('D') || Keyboard::Get()->Up('D') || (Keyboard::Get()->Up(0x0001) && direction == 3))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"IdleRT");
		direction = 3;
	}

	// �ȱ�
	if (Keyboard::Get()->Press('S'))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"RunBT");
	}
	else if (Keyboard::Get()->Press('W'))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"RunUP");
	}
	else if (Keyboard::Get()->Press('A'))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"RunLT");
	}
	else if (Keyboard::Get()->Press('D'))
	{
		player->GetAnimator()->SetCurrentAnimClip(L"RunRT");
	}
}

void Player::Hp(string type,  int hp)
{
	if (type == "passive")
	{
		// 1. �⺻ Hp�� �нú��� hp������ ����
		characterHp += hp;
	}
	else if (type == "potion")
	{
		// 2. ���ǻ�� �� ���� ü�¿� + ����
		characterHp += 50;
	}
	else if (type == "dmg")
	{
		// 3. �ǰ� �� ���� ü�¿� - ����
		characterHp -= hp;
	}
}

void Player::Attack()
{
	// ����
	if (Keyboard::Get()->Press(0x0001))
	{
		switch (direction)
		{
		case 0:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackBT");
			break;
		case 1:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackUP");
			break;
		case 2:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackLT");
			break;
		case 3:
			player->GetAnimator()->SetCurrentAnimClip(L"AttackRT");
			break;
		}
	}
}

void Player::Defence()
{
	// �ǰ�
	if (dmg && direction == 0)
	{
		Hp("dmg", 10);
		// �����ִ� ������ ��ġ���� �ڷ� ����(0.5cm?) �����̵��� ����
	}

	// ���
	if (dmg && characterHp == 0)
	{
		switch (direction)
		{
		case 0:
			player->GetAnimator()->SetCurrentAnimClip(L"DieBT");
			break;
		case 1:
			player->GetAnimator()->SetCurrentAnimClip(L"DieUP");
			break;
		case 2:
			player->GetAnimator()->SetCurrentAnimClip(L"DieLT");
			break;
		case 3:
			player->GetAnimator()->SetCurrentAnimClip(L"DieRT");
			break;
		}
	}
}

void Player::Inventory()
{
	// ����
	if (Keyboard::Get()->Press('Q'))
	{
		if (potionCount != 0)
		{
			potionCount--;
		}
	}

	// ���
}

void Player::Interaction()
{
	// ��ȣ�ۿ�?
	// �нú� ����

	// ��� ��ü?
}