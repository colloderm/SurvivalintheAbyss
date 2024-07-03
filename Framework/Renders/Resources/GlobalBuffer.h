#pragma once
#include "Framework.h"

/*
WVP�� 3D������ ���� 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ���� �� �ϳ��̴�.
����Ͱ� 2D�̱� ������ 3D���ӵ� 2D��ǥ�� ��ȯ �� �ʿ䰡 �ִ�.

World // ����
- ���� ������ �۷ι� ��ǥ���� ���� ��ǥ�� ��ȯ�ϴ� ���� �ǹ�
- ���� ��ġ, ȸ��, ũ�� ���� ����.

View // ī�޶�
- �۷ι� ��ǥ���� ī�޶� �ٶ󺸴� ������ ��Ÿ��
// ���� ī�޶� ��ü�� �ִ°� �ƴ�
- ī�޶��� ��ġ, ����, �þ߸� ����.

projection // ����
- 3D������ 2D ��ũ�� ��ǥ�� ��ȯ��Ű�� ���
- �þ߰�, ��Ⱦ��, ũ���� ���(�ܸ鵵)���� ����Ͽ� ����.

WVP�� �����Ͽ� DirectX���� �׸����� �ݵ��
World * View * Projection�� ������ ���ؾ� �Ѵ�. // DirectX�� �׷��� ����
*/

class WorldBuffer : public ShaderBuffer
{
public:

	WorldBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		// ��� �ʱ�ȭ
		// ����� ������ �ִ� ��� �����͸� 0���� �ʱ�ȭ
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(Matrix world)
	{
		// ��ġ ���
		// ��> ���� ���� ���� �ٲ�� ��ȯ
		// world�� ���� ������.������ ��, world�� ���� ������.������ ��
		D3DXMatrixTranspose(&data.world, &world);
	}

	// CPU���� GPU�� �ѱ� �������� ����ü
	// �޸� �Ҵ緮�� ���� 16�� ����� ũ�⸦ �Ҵ������� ������ ������ ����.
	// Ex) int(4Byte) 4�� == 16Byte / char(1Byte) 32�� == 32Byte
	// Ex) 16, 32, 64 ...
	struct Data
	{
		Matrix world; // Matrix = float 16�� == 64Byte(16*4)�� ũ�Ⱑ ��(�ƹ�ư ũ���)
		// ���࿡ �޸� �Ҵ緮�� ������ ������� ���� �����͸� �߰��� �־��� ��� �̷��� �����͸� �е� �����Ͷ� �θ���.
		// int padding // int dummy
	};

private:
	Data data;
};

class VPBuffer : public ShaderBuffer
{
public:

	VPBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.proj);
	}

	void SetView(Matrix view)
	{
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProj(Matrix proj)
	{
		D3DXMatrixTranspose(&data.proj, &proj);
	}

	struct Data
	{
		Matrix view;	// ī�޶�
		Matrix proj;	// ������(�þ�)
	};

private:
	Data data;
};