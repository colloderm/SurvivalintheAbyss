#pragma once

class TileSet
{
public:
	friend class TMap;

	TileSet(wstring imagePath, UINT xCount, UINT yCount);
	~TileSet();

	void GUI();

	ID3D11ShaderResourceView* GetSRV() { return tileSRV; }

	void ChangeTileMap(wstring imagePath, uint xCount, uint yCount);

	wstring GetTilePath() { return tilePath; }

	UINT GetXCount() { return tileXCount; }
	UINT GetYCount() { return tileYCount; }

private:
	ID3D11ShaderResourceView* tileSRV = nullptr;

	// Ÿ�ϸ� �̹����� ���������� �ڸ�����
	UINT tileXCount = 0;
	UINT tileYCount = 0;

	// �÷��̾ ������ Ÿ���� ���� uv
	Vector2 selectedStartUV = Values::ZeroVec2;

	// Ÿ�� ��ĭ�� ���� �׸� uv��
	Vector2 texelTileSize = Values::ZeroVec2;

	wstring tilePath = L"";
};