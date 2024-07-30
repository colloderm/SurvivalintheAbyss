#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/PlayerAsset.h"
#include "Demos/MonsterAsset.h"
#include "Demos/StartStage.h"


void Program::Init()
{
	States::Create();
	Camera::Create();

	// Push(new PlayerAsset);
	// Push(new MonsterAsset);

	Push(new StartStage);
}

void Program::Destroy()
{
	Camera::Delete();

	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	Camera::Get()->Update();

	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	Camera::Get()->Render();

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame"; //Ã¢ÀÌ¸§
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
