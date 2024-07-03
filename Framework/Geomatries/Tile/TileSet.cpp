#include "Framework.h"
#include "TileSet.h"

TileSet::TileSet(wstring imagePath, UINT xCount, UINT yCount)
	: tilePath(imagePath), tileXCount(xCount), tileYCount(yCount)
{
	Texture2D* tex = new Texture2D(tilePath);

	tileSRV = tex->GetSRV();
	SAFE_DELETE(tex);

	texelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);
}

TileSet::~TileSet()
{
}

void TileSet::GUI()
{
	// 여러 타일셋이 있을때 겹치지 않도록 이름 구분
	string temp = to_string((uint)this) + "TileSet";
	ImGui::Begin(temp.c_str());
	{
		int count = 0;
		for (UINT y = 0; y < tileYCount; y++)
		{
			for (UINT x = 0; x < tileXCount; x++)
			{
				float startX = texelTileSize.x * x;
				float startY = texelTileSize.y * y;

				// PushID = 다음에 있는 GUI기능에 고유한 ID 부여
				ImGui::PushID(count);

				// ImageButton은 그림이 그려져있는 버튼 구현
				// SRV, 버튼 크기, 이미지 startUV, endUV
				if (ImGui::ImageButton(tileSRV, ImVec2(40, 40), 
					ImVec2(startX, startY), 
					ImVec2(startX + texelTileSize.x, startY + texelTileSize.y)))
				{
					selectedStartUV = Vector2(startX, startY);
				}

				count++;

				ImGui::PopID();

				// count의 번호가 xCount보다 작다면 같은 라인에 세우기
				if (count % tileXCount != 0)
					ImGui::SameLine();
			}
		}
	}
	ImGui::End();
}

void TileSet::ChangeTileMap(wstring imagePath, uint xCount, uint yCount)
{
	tilePath = imagePath;

	Texture2D* tex = new Texture2D(tilePath);

	tileSRV = tex->GetSRV();
	SAFE_DELETE(tex);

	tileXCount = xCount;
	tileYCount = yCount;

	texelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);
}
