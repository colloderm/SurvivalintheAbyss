#include "stdafx.h"
#include "03_ShadedDemo.h"

void ShadedDemo::Init()
{
	st = new ShadedTexture({ 640, 360, 0 }, { 500, 500, 1 }, 0.0f, TexturePath + L"PandaSample.jpg");
}

void ShadedDemo::Destroy()
{
	SAFE_DELETE(st);
}

void ShadedDemo::Update()
{
	st->Update();
}

void ShadedDemo::Render()
{
	st->Render();
}

void ShadedDemo::PostRender()
{
}

void ShadedDemo::GUI()
{
	st->GUI();
}
