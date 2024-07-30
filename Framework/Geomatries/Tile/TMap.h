#pragma once

#include "Tile.h"
#include "TileSet.h"

class IndexNumBuffer : public ShaderBuffer
{
public:

	// 타일의 위치를 명확하게 알려주기 위한 쉐이더 버퍼
	IndexNumBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.index = 0;
	}

	void SetIndex(uint index) { data.index = index; }

	struct Data
	{
		uint index;
		Vector3 dummy;
	};

private:
	Data data;
};

class TMap
{
public:

	// width = 가로에 깔 타일의 개수
	// height = 세로에 깔 타일의 개수
	// spacing = 한 타일의 가로, 세로 길이 // 정사각형
	// width, height 가 10이고, spacing이 20이면 
	// 가로 세로 각각의 10개씩 즉, 총 100개의 타일이 
	// 각각의 20만큼의 크기 즉, 대략 2000, 2000 크기의 타일맵이 만들어진다.
	TMap(uint width, uint height, uint spacing);
	~TMap();

	void Update();
	void Render();
	void GUI();

	void GenerateTileMap();

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void Save(string path);
	void Load(string path);

	Tile* GetTile(Vector3 mPos);

	void MakeTSet(wstring path, UINT xCount, UINT yCount);
	TileSet* GetTSet() { return tSet; }

private:
	vector<VertexTile> vertices;
	VertexBuffer* vb = nullptr;

	InputLayout* il = nullptr;

	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world = Values::Identity;
	WorldBuffer* wb = nullptr;

	IndexNumBuffer* inb = nullptr;

	UINT width = 0;
	UINT height = 0;
	UINT spacing = 0;

	D3D11_MAPPED_SUBRESOURCE subRe;

	Tile** tiles = nullptr;
	TileSet* tSet = nullptr;

	ID3D11SamplerState* sampler = nullptr;
	ID3D11BlendState* blend = nullptr;
};