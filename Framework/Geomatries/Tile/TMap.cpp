#include "Framework.h"
#include "TMap.h"

TMap::TMap(uint width, uint height, uint spacing)
	: width(width), height(height), spacing(spacing)
{
	GenerateTileMap();

	vertices.assign(4, VertexTile());

	vertices[0].position = Vector3(0, 0, 0);
	vertices[1].position = Vector3(0, (float)spacing, 0);
	vertices[2].position = Vector3((float)spacing, 0, 0);
	vertices[3].position = Vector3((float)spacing, (float)spacing, 0);

	indices = { 0, 1, 2, 2, 1, 3 };

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"VertexTile.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"VertexTile.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexTile::descs, VertexTile::count, vs->GetBlob());

	wb = new WorldBuffer();
	wb->SetWorld(world);

	inb = new IndexNumBuffer();
	inb->SetIndex(0);
}

TMap::~TMap()
{
	if (tSet != nullptr)
		SAFE_DELETE(tSet);

	// tiles의 x데이터 지우기
	for (uint y = 0; y < height; y++)
		SAFE_DELETE_ARRAY(tiles[y]);

	// tiles의 y데이터 지우기
	SAFE_DELETE_ARRAY(tiles);

	SAFE_DELETE(inb);
	SAFE_DELETE(wb);

	SAFE_DELETE(il);

	SAFE_DELETE(ps);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void TMap::Update()
{
	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Down('S'))
		{
			string tileName;
			cin >> tileName;
			getchar(); // 엔터키 지우는 용도
			Path::CreateFolders(TilePath);
			Save(TilePath + tileName + ".data");
			Save(TilePath + tileName + ".txt");
		}

		if (Keyboard::Get()->Down('L'))
		{
			string tileName;
			cin >> tileName;
			getchar();
			Load(TilePath + tileName + ".data");
		}
	}

	// 카메라에게 마우스 위치 받아오기
	Vector3 mPos = Camera::Get()->GetMPosition();

	// 마우스 위치에 있는 타일 확인하기
	Tile* tile = GetTile(mPos);

	// 외각선 그리기 위해 타일 번호 알려주기
	if (tile != nullptr)
		inb->SetIndex(tile->GetIndex());

	// 좌클릭 시
	if (Mouse::Get()->Press(0x0000))
	{
		if (tile != nullptr)
		{
			Vector2 startUV = tSet->selectedStartUV;
			Vector2 endUV = startUV + tSet->texelTileSize;
			tile->SetStartUV(startUV);
			tile->SetEndUV(endUV);
		}
	}
}

void TMap::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();

	DC->PSSetShaderResources(0, 1, &tSet->tileSRV);

	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			Tile& tile = tiles[y][x];

			MapVertexBuffer();
			{
				for (VertexTile& v : vertices)
				{
					v.color = tile.GetColor();
					v.index = tile.GetIndex();
				}

				// TMap에 그려질 타일 하나의 위치 값
				// 모든 타일이 이 작업을 수행한다.
				// 1   3
				// 0   2
				vertices[0].uv = Vector2(tile.GetStartUV().x, tile.GetEndUV().y);
				vertices[1].uv = Vector2(tile.GetStartUV());
				vertices[2].uv = Vector2(tile.GetEndUV());
				vertices[3].uv = Vector2(tile.GetEndUV().x, tile.GetStartUV().y);

				// 외곽선 그리기 위한 uv2
				vertices[0].uv2 = Vector2(0, 1);
				vertices[1].uv2 = Vector2(0, 0);
				vertices[2].uv2 = Vector2(1, 1);
				vertices[3].uv2 = Vector2(1, 0);
			}
			UnmapVertexBuffer();

			world = DXMath::Translation(tile.GetPosition());
			wb->SetWorld(world);
			wb->SetVSBuffer(0);
			inb->SetPSBuffer(0);

			DC->DrawIndexed(ib->GetCount(), 0, 0);
		}
	}
}

void TMap::GUI()
{
	tSet->GUI();
}

void TMap::GenerateTileMap()
{
	// 타일 깔아주는 함수
	if (width == 0 || height == 0 || spacing == 0)
		assert(false); // 프로그램 폭파

	// tiles의 더블 포인터를 특정 함수에 건내주기 위한 용도가 아닌 이중 배열로써 사용
	tiles = new Tile * [height];
	int index = 0;
	for (uint y = 0; y < height; y++)
	{
		tiles[y] = new Tile[width];

		for (uint x = 0; x < width; x++)
		{
			tiles[y][x].SetPosition(Vector3((float)(x * spacing), (float)(y * spacing), 0.0f));
			tiles[y][x].SetIndex(index++);
		}
	}
}

void TMap::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
}

void TMap::UnmapVertexBuffer()
{
	memcpy(subRe.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}

void TMap::Save(string path)
{
    // out file stream
    // 출력 파일 스트림
    ofstream fout(path);

    // cout이랑 형태가 비슷함
    // 아래의 순서의 데이터를 차곡차곡 적어넣는다.
    // .data가 아니라 .txt로 출력하면 그대로 읽을수도 있을꺼임
    fout << to_string(width) << ' ' << to_string(height) << ' ' << to_string(spacing) << endl;

    string imagePath = "";
    wstring tilePath = tSet->GetTilePath();
    imagePath.assign(tilePath.begin(), tilePath.end());
    string xCount = to_string(tSet->GetXCount());
    string yCount = to_string(tSet->GetYCount());

    fout << imagePath << ' ' << xCount << ' ' << yCount << endl;

    for (uint y = 0; y < height; y++)
    {
        for (uint x = 0; x < width; x++)
        {
            Tile& tile = tiles[y][x];
            string output;
            // startUV 입력
            output += to_string(tile.GetStartUV().x) + ' ' + to_string(tile.GetStartUV().y) + ' ';
            // endUV 입력
            output += to_string(tile.GetEndUV().x) + ' ' + to_string(tile.GetEndUV().y);

            fout << output << endl;
        }
    }
}

void TMap::Load(string path)
{
    // in file stream
    ifstream fin(path);

    // 파일 있는지 확인
    if (fin.fail())
        assert(false); // 없으면 폭파

    // tiles x좌표 데이터 지우기
    for (uint y = 0; y < height; y++)
        SAFE_DELETE_ARRAY(tiles[y]);

    // tiles y좌표 데이터 지우기
    SAFE_DELETE_ARRAY(tiles);

    // ifsteam에서 받아온 데이터들을 임시로 저장할 공간
    char temp[256];

    // Width, Height, Spacing 불러오기
    {
        // getline을 이용해 한줄의 데이터를 뽑아서 temp에 집어넣기
        fin.getline(temp, 256);
        string t = "";

        for (int i = 0; i < 256; i++)
        {
            // 데이터가 스페이스바가 아니고
            // 널문자도 아니라면 해당 데이터를
            // string에 넣어두기
            if (temp[i] != ' ' && temp[i] != '\0')
                t += temp[i];
            else
            {
                if (width == 0)
                {
                    width = stoi(t);
                    t.clear();
                }
                else if (height == 0)
                {
                    height = stoi(t);
                    t.clear();
                }
                else if (spacing == 0)
                {
                    spacing = stoi(t);
                    break;
                }
                continue;
            }
        }

        cout << "타일맵 불러오기 : " << path << endl;
        cout << "Width : " << width << endl;
        cout << "Height : " << height << endl;
        cout << "Spacing : " << spacing << endl;

        if (width == 0 || height == 0 || spacing == 0)
            assert(false);
    }

    // TileSet image 정보 불러오기
    {
        fin.getline(temp, 256);
        string t = "";

        uint count = 0;
        string imagePath = "";
        uint xCount = 0;
        uint yCount = 0;

        for (int i = 0; i < 256; i++)
        {
            if (temp[i] != ' ' && temp[i] != '\0')
                t += temp[i];
            else if (count == 0)
            {
                imagePath = t;
                t.clear();
                count++;
            }
            else if (count == 1)
            {
                xCount = stoi(t);
                t.clear();
                count++;
            }
            else if (count == 2)
            {
                yCount = stoi(t);
                t.clear();

                wstring temp = L"";
                temp.assign(imagePath.begin(), imagePath.end());

                tSet->ChangeTileMap(temp, xCount, yCount);

                break;
            }
        }

        cout << "ImagePath : " << imagePath << endl;
        cout << "xCount : " << xCount << endl;
        cout << "yCount : " << yCount << endl;
    }


    tiles = new Tile * [height];
    int count = 0;

    for (uint y = 0; y < height; y++)
    {
        tiles[y] = new Tile[width];
        for (uint x = 0; x < width; x++)
        {
            // 타일 새로 깔기
            tiles[y][x].SetPosition(Vector3((float)(x * spacing), (float)(y * spacing), 0.0f));
            tiles[y][x].SetIndex(count);
            count++;

            fin.getline(temp, 256);
            Vector2 uv;
            string t;

            int flag = 0;
            for (int i = 0; i < 256; i++)
            {
                // i = 0 ~ 8
                // float은 소숫점 포함 8자리이기 때문에
                // 8문자씩 읽어들인다.
                if ((i + 1) % 9 == 0)
                {
                    if (flag == 0)
                    {
                        uv.x = stof(t);
                        flag++;

                        // cout << "StartUV.x : " << uv.x << endl;
                    }
                    else if (flag == 1)
                    {
                        uv.y = stof(t);
                        flag++;
                        tiles[y][x].SetStartUV(uv);

                        // cout << "StartUV.y : " << uv.y << endl;

                        uv = Values::ZeroVec2;
                    }
                    else if (flag == 2)
                    {
                        uv.x = stof(t);
                        flag++;

                        // cout << "EndUV.x : " << uv.x << endl;
                    }
                    else if (flag == 3)
                    {
                        uv.y = stof(t);
                        flag++;

                        tiles[y][x].SetEndUV(uv);

                        // cout << "EndUV.y : " << uv.y << endl;
                        break;
                    }

                    t.clear();
                    continue;
                }
                else
                {
                    t += temp[i];
                }
            }
        }
    }

    // 백업본 생성
    Save(TilePath + "After.txt");
}

Tile* TMap::GetTile(Vector3 mPos)
{
	uint x = (int)mPos.x / spacing;
	uint y = (int)mPos.y / spacing;

	if (x < 0 || x >= width || y < 0 || y >= height)
		return nullptr;

	return &tiles[y][x];
}

void TMap::MakeTSet(wstring path, UINT xCount, UINT yCount)
{
	if (tSet == nullptr)
		tSet = new TileSet(path, xCount, yCount);
}
