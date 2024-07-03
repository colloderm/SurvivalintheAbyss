#pragma once

// 색이 있는 네모를 그리기 위한 정점 데이터
struct VertexColor
{
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0) {}
	VertexColor(Vector3 position, Color color)
		: position(position), color(color) {}

	Vector3 position;	// 정점의 위치
	Color color;		// 정점의 색상

	// 정점 데이터의 구조를 서술해 줄 구조체.
	static D3D11_INPUT_ELEMENT_DESC descs[];
	// 요소 개수
	static const UINT count = 2; // 2인 이유는 position과 color 2개가 있기 때문
};

// 그림이 있는 네모를 그리기 위한 정점 데이터
struct VertexTexture
{
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}
	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv) {}

	Vector3 position;	// 정점의 위치
	Vector2 uv;			// 그림의 좌표

	// 정점 데이터의 구조를 서술해 줄 구조체.
	static D3D11_INPUT_ELEMENT_DESC descs[];
	// 요소 개수
	static const UINT count = 2; // 2인 이유는 position과 uv 2개가 있기 때문
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