#include "stdafx.h"
#include "04_AnimDemo.h"

void AnimDemo::Init()
{
	ar = new AnimationRect({ 200, 360, 0 }, { 300, 300, 1 });
	wolf = new Wolf({ 600, 360, 0 }, { 300, 300, 1 });
	wolf2 = new Wolf({ 700, 360, 0 }, { 100, 100, 1 });

	Sounds::Get()->AddSound("BGM", SoundPath + L"bgm.wav", true);
	Sounds::Get()->Play("BGM");

	Sounds::Get()->AddSound("Click", SoundPath + L"shot.wav");

	rd = new RectDemo();
	rd->Init();
	cd = new CollisionDemo();
	cd->Init();
	td = new TextureDemo();
	td->Init();
}

void AnimDemo::Destroy()
{
	SAFE_DELETE(wolf2);
	SAFE_DELETE(wolf);
	SAFE_DELETE(ar);
}

void AnimDemo::Update()
{
	if (Mouse::Get()->Down(0x0000))
	{
		//Camera::Get()->SetTarget(ar);
		ar->SetPosition(Camera::Get()->GetMPosition());

		Sounds::Get()->Play("Click");
	}
	else if (Mouse::Get()->Down(0x0001))
	{
		Camera::Get()->DelTarget();
	}

	if (Keyboard::Get()->Down(VK_F9))
	{
		demoCount++;
	}

	/*if (Keyboard::Get()->Press('W'))
	{
		ar->GetAnimator()->SetCurrentAnimClip(L"WalkUR");
	}
	else if (Keyboard::Get()->Press('A'))
	{
		ar->GetAnimator()->SetCurrentAnimClip(L"WalkUL");
	}
	else if (Keyboard::Get()->Press('S'))
	{
		ar->GetAnimator()->SetCurrentAnimClip(L"WalkDL");
	}
	else if (Keyboard::Get()->Press('D'))
	{
		ar->GetAnimator()->SetCurrentAnimClip(L"WalkDR");
	}*/

	ar->Update();
	wolf->Update();
	wolf2->Update();

	if (demoCount == 0)
	{
		rd->Update();
	}
	else if (demoCount == 1)
	{
		td->Update();
		ar->SetPosition({ 100, 300, 1 });
	}
	else if (demoCount == 2)
	{
		cd->Update();
		demoCount = 0;
	}
}

void AnimDemo::Render()
{
	if (demoCount == 0)
	{
		rd->Render();
	}
	else if (demoCount == 1)
	{
		td->Render();
	}
	else if (demoCount == 2)
	{
		cd->Render();
	}
	ar->Render();
	wolf->Render();
	wolf2->Render();
}

void AnimDemo::PostRender()
{
}

void AnimDemo::GUI()
{
}
