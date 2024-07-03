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

	// 타일맵 이미지를 몇조각으로 자를건지
	UINT tileXCount = 0;
	UINT tileYCount = 0;

	// 플레이어가 선택한 타일의 시작 uv
	Vector2 selectedStartUV = Values::ZeroVec2;

	// 타일 한칸에 대한 그림 uv값
	Vector2 texelTileSize = Values::ZeroVec2;

	wstring tilePath = L"";
};