#include "stdafx.h"
#include "01_CollisionDemo.h"

void CollisionDemo::Init()
{
	player = new Rect({ 415, 300, 0 }, { 100, 100, 1 });
	other = new Rect({ 300, 300, 0 }, { 100, 100, 1 });

	for (int i = 0; i < oc; i++)
	{
		others.push_back(new Rect({ 600, 100 + (float)i * 20, 0 }, { 10, 10, 1 }));
		others[i]->UpdateWorld();
	}

	player->UpdateWorld();
	other->UpdateWorld();
}

void CollisionDemo::Destroy()
{
	for (Rect* r : others)
	{
		SAFE_DELETE(r);
	}

	SAFE_DELETE(other);
	SAFE_DELETE(player);
}

void CollisionDemo::Update()
{
	player->Move();

	//Down(): ������ //Press: ������ �ִ� ����
	//if (Mouse::Get()->Down(0x000000)); // 0x000000: ��Ŭ�� // 0x000001: ��Ŭ�� // 0x000002: ��Ŭ��
	//{
	//	player->SetPosition(Mouse::Get()->GetPosition());
	//}

	if (BoundingBox::AABB(player->GetCollision(), other->GetCollision()) ||
		BoundingBox::OBB(player->GetCollision(), other->GetCollision())) // player�� other �浹 �� �� ����
	{
		//other->SetPosition({ (float)Random::GetRandomInt(300, 1000), 300, 0 }); // ���� �̵�
		other->SetColor({ 0, 1, 0, 1 }); // ���
	}
	else // �� �浹 �� �� ����
	{
		other->SetColor({ 1, 0, 0, 1 }); // ������
	}

	for (Rect* r : others)
	{
		if (BoundingBox::AABB(player->GetCollision(), r->GetCollision()) ||
			BoundingBox::OBB(player->GetCollision(), r->GetCollision()))
		{
			r->SetColor({ 0, 1, 0, 1 });
		}
		else
		{
			r->SetColor({ 1, 0, 0, 1 });
		}

		r->Update();
	}

	 // �浹 üũ Ȯ�� �� �� ���� // init�� UpdateWorld ������ if���� �����ϸ� ��
	player->Update();
	other->Update();
}

void CollisionDemo::Render()
{
	player->Render(); // ���콺 ���� �� �ּ�ó���ϸ� �ڽ��� �����Ǿ����� �Ⱥ��� (�浹ó�� ����)
	other->Render();

	for (Rect* r : others)
	{
		r->Render();
	}
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI() //�׽�Ʈ �ܿ��� �ּ�
{
	player->GUI();
	other->GUI();
}
