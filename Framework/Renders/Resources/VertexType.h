#pragma once

// ���� �ִ� �׸� �׸��� ���� ���� ������
struct VertexColor
{
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0) {}
	VertexColor(Vector3 position, Color color)
		: position(position), color(color) {}

	Vector3 position;	// ������ ��ġ
	Color color;		// ������ ����

	// ���� �������� ������ ������ �� ����ü.
	static D3D11_INPUT_ELEMENT_DESC descs[];
	// ��� ����
	static const UINT count = 2; // 2�� ������ position�� color 2���� �ֱ� ����
};

// �׸��� �ִ� �׸� �׸��� ���� ���� ������
struct VertexTexture
{
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}
	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv) {}

	Vector3 position;	// ������ ��ġ
	Vector2 uv;			// �׸��� ��ǥ

	// ���� �������� ������ ������ �� ����ü.
	static D3D11_INPUT_ELEMENT_DESC descs[];
	// ��� ����
	static const UINT count = 2; // 2�� ������ position�� uv 2���� �ֱ� ����
};

struct VertexTile
{
	VertexTile() : position(Values::ZeroVec3), uv(Values::ZeroVec2), color(0, 0, 0, 0)
	{}

	VertexTile(Vector3 position, Vector2 uv, Vector2 uv2, Color color, uint index)
			: position(position), uv(uv), uv2(uv2), color(color), index(index)
	{}

	Vector3 position;
	Vector2 uv;
	Vector2 uv2;
	Color color;
	uint index;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 5;
};