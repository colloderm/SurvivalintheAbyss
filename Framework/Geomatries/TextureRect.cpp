#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		vertices.assign(4, VertexTexture());

		// 네모 중점(0,0) 기준 // 네모 정점의 각 사이값을 1로 했을경우
		// 좌 하단
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		// 우 상단
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// 우 하단
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// 좌 상단
		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);
	}

	//VertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// Indices // IndexBuffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// VertexShader
	{
		vs = new VertexShader();
		// 쉐이더 경로 + 쉐이더 파일 이름, 실행할 함수 이름
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	// WorldBuffer
	{
		wb = new WorldBuffer();
	}

	// Collision
	{
		collision = new BoundingBox();
		edge = new RectEdge();

		for (int i = 0; i < 4; i++)
			verticesLocalPosition[i] = vertices[i].position;
	}
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		vertices.assign(4, VertexTexture());

		// 네모 중점(0,0) 기준 // 네모 정점의 각 사이값을 1로 했을경우
		// 좌 하단
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		// 우 상단
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// 우 하단
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// 좌 상단
		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);
	}

	//VertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// Indices // IndexBuffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// VertexShader
	{
		vs = new VertexShader();
		// 쉐이더 경로 + 쉐이더 파일 이름, 실행할 함수 이름
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	// WorldBuffer
	{
		wb = new WorldBuffer();
	}

	// Collision
	{
		collision = new BoundingBox();
		edge = new RectEdge();

		for (int i = 0; i < 4; i++)
			verticesLocalPosition[i] = vertices[i].position;
	}

	// Rasterizer State
	// 래스터라이저는 VS로 찍은 정점과 정점 사이를 채워주는 역할을 해주며, 따로 지정하거나 생성하지 않아도 기본값이 존재하긴 하지만,
	// 좀 더 확실하거나 정교한 작업이 필요할 경우 만들어 사용하기도 한다.
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		// CullMode == 그리지 않을 부분 설정
		// D3D11_CULL_BACK == 뒷면을 지우겠다.
		desc.CullMode = D3D11_CULL_BACK;

		// FillMode == 어떻게 채울지 설정
		// D3D11_FILL_SOLID == 꽉 채우겠다.
		// D3D11_FILL_WIREFRAME == 외곽선만 그린다 // 안그려진다 != 투명해진다.
		desc.FillMode = D3D11_FILL_SOLID;

		// 반시계 방향으로 그릴지 설정
		desc.FrontCounterClockwise = false;

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
		CHECK(hr);
	}

	// SRV
	// SRV는 그림의 데이터라고 할 수 있고 그림이 가지고 있는 픽셀들의 정보를 담고 있다.
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			DEVICE,
			path.c_str(),
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		CHECK(hr);
	}
}

TextureRect::~TextureRect()
{
	SAFE_RELEASE(srv);
	SAFE_RELEASE(rs);

	SAFE_DELETE(collision);
	SAFE_DELETE(edge);

	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);

}

void TextureRect::Update()
{
	UpdateWorld();
}

void TextureRect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	wb->SetVSBuffer(0);

	ps->SetShader();

	DC->PSSetShaderResources(0, 1, &srv);
	DC->RSSetState(rs);

	// 최종적으로 그림을 그리는 코드
	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
	// rect에 있는거 가져와서 이름만 바꾸면 됨
}

void TextureRect::UpdateWorld()
{
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);

	collision->UpdateCollisionData(world, verticesLocalPosition);
}

string TextureRect::MakeLabel(string label)
{
	return string();
}

void TextureRect::Move(int moveCheck)
{
	if (moveCheck == 1)
	{
		if (bJump == false)
		{
			if (Keyboard::Get()->Down('S') || Keyboard::Get()->Down(VK_DOWN))
			{
				SetImage(TexturePath + L"Dino_D2.png");
				size = Vector3(70, 40, 0);
				position = Vector3(100, 100 + size.y / 2, 0);
				bDown = true;
			}
			if (Keyboard::Get()->Up('S') || Keyboard::Get()->Up(VK_UP))
			{
				SetImage(TexturePath + L"Dino_Nonal.png");
				size = Vector3(70, 80, 0);
				position = Vector3(100, 95 + size.y / 2, 0);
				bDown = false;
			}
			if (Keyboard::Get()->Press('S') || Keyboard::Get()->Press(VK_DOWN))
			{
				if (!bDown)
				{
					SetImage(TexturePath + L"Dino_D2.png");
					size = Vector3(70, 40, 0);
					position = Vector3(100, 100 + size.y / 2, 0);
					bDown = true;
				}
			}
		}



		if (Keyboard::Get()->Down(VK_SPACE) ||
			Keyboard::Get()->Down(VK_UP) ||
			Keyboard::Get()->Down('W'))
		{
			if (jumpCount < 12 && bJump == false && bDown == false)
			{

				bJump = true;
				if (jumpCount == 0) jumpStartY = position.y;
				else if (jumpCount > 0)
				{
					uCurJumpT = 0;
					dCurJumpT = 0 - (maxJumpT - dCurJumpT);
					curJumpSpd = maxJumpSpd;
					bFall = false;
				}
				jumpCount++;
			}
		}

		if (bJump == true)
		{
			// 추락하고 있지 않다 == 상승중
			if (bFall == false)
			{
				// 점프시간이 초과했다면
				if (uCurJumpT >= maxJumpT)
				{
					uCurJumpT = 0.0f;

					bFall = true;
				}
				else // 점프를 계속 해야한다면
				{
					curJumpSpd -= maxJumpSpd * Time::Delta();

					position.y += curJumpSpd * 2.0f;

					uCurJumpT += Time::Delta();
				}
			}
			else // bFall == true // 하강중
			{
				if (dCurJumpT >= maxJumpT)
				{
					curJumpSpd = maxJumpSpd;
					dCurJumpT = 0.0f;
					position.y = jumpStartY;
					jumpCount = 0;

					bJump = false;
					bFall = false;

				}
				else
				{
					curJumpSpd += maxJumpSpd * Time::Delta();

					position.y -= curJumpSpd * 2.0f;

					if (position.y <= jumpStartY)
					{
						position.y = jumpStartY;
						dCurJumpT = maxJumpT;
					}
					dCurJumpT += Time::Delta();
				}
			}
		}
	}
}

void TextureRect::Move2(int move2Check)
{
	if (move2Check == 1)
	{
		position.x -= 300.0f * Time::Delta();
		if (position.x <= -300)
		{
			position.x = (float)Random::GetRandomInt(1500, 2500);
		}
	}
}

void TextureRect::SetImage(wstring imagePath)
{
	SAFE_RELEASE(srv); // 한번 지우지 않으면 최적화 망함
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,
		imagePath.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	CHECK(hr);
}

void TextureRect::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderPath, "VS");
	ps->Create(shaderPath, "PS");
}
