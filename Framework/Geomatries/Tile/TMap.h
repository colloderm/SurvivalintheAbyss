#pragma once

#include "Tile.h"
#include "TileSet.h"

class IndexNumBuffer : public ShaderBuffer
{
public:

	// Ÿ���� ��ġ�� ��Ȯ�ϰ� �˷��ֱ� ���� ���̴� ����
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

	// width = ���ο� �� Ÿ���� ����
	// height = ���ο� �� Ÿ���� ����
	// spacing = �� Ÿ���� ����, ���� ���� // ���簢��
	// width, height �� 10�̰�, spacing�� 20�̸� 
	// ���� ���� ������ 10���� ��, �� 100���� Ÿ���� 
	// ������ 20��ŭ�� ũ�� ��, �뷫 2000, 2000 ũ���� Ÿ�ϸ��� ���������.
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