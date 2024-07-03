#include "stdafx.h"
#include "02_TextureDemo.h"

void TextureDemo::Init()
{
	tr = new TextureRect({ 640, 360, 0 }, { 500, 500, 1 }, 0.0f, TexturePath + L"Dino_Nonal.png");
}

void TextureDemo::Destroy()
{
	SAFE_DELETE(tr);
}

void TextureDemo::Update()
{
	tr->Update();
}

void TextureDemo::Render()
{
	tr->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
}
