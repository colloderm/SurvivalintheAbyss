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

	//Down(): 누를때 //Press: 누르고 있는 상태
	//if (Mouse::Get()->Down(0x000000)); // 0x000000: 좌클릭 // 0x000001: 우클릭 // 0x000002: 휠클릭
	//{
	//	player->SetPosition(Mouse::Get()->GetPosition());
	//}

	if (BoundingBox::AABB(player->GetCollision(), other->GetCollision()) ||
		BoundingBox::OBB(player->GetCollision(), other->GetCollision())) // player와 other 충돌 시 색 변경
	{
		//other->SetPosition({ (float)Random::GetRandomInt(300, 1000), 300, 0 }); // 랜덤 이동
		other->SetColor({ 0, 1, 0, 1 }); // 녹색
	}
	else // 미 충돌 시 색 원복
	{
		other->SetColor({ 1, 0, 0, 1 }); // 빨간색
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

	 // 충돌 체크 확인 후 색 적용 // init에 UpdateWorld 없으면 if위에 설정하면 됨
	player->Update();
	other->Update();
}

void CollisionDemo::Render()
{
	player->Render(); // 마우스 설정 후 주석처리하면 박스는 생성되었지만 안보임 (충돌처리 가능)
	other->Render();

	for (Rect* r : others)
	{
		r->Render();
	}
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI() //테스트 외에는 주석
{
	player->GUI();
	other->GUI();
}
