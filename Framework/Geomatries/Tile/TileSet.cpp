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
	// ���� Ÿ�ϼ��� ������ ��ġ�� �ʵ��� �̸� ����
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

				// PushID = ������ �ִ� GUI��ɿ� ������ ID �ο�
				ImGui::PushID(count);

				// ImageButton�� �׸��� �׷����ִ� ��ư ����
				// SRV, ��ư ũ��, �̹��� startUV, endUV
				if (ImGui::ImageButton(tileSRV, ImVec2(40, 40), 
					ImVec2(startX, startY), 
					ImVec2(startX + texelTileSize.x, startY + texelTileSize.y)))
				{
					selectedStartUV = Vector2(startX, startY);
				}

				count++;

				ImGui::PopID();

				// count�� ��ȣ�� xCount���� �۴ٸ� ���� ���ο� �����
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
