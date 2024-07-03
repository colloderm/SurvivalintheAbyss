#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// Vertices
	{
		vertices.assign(4, VertexTexture());

		// �׸� ����(0,0) ���� // �׸� ������ �� ���̰��� 1�� �������
		// �� �ϴ�
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		// �� ���
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// �� �ϴ�
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// �� ���
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
		// ���̴� ��� + ���̴� ���� �̸�, ������ �Լ� �̸�
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

		// �׸� ����(0,0) ���� // �׸� ������ �� ���̰��� 1�� �������
		// �� �ϴ�
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		// �� ���
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		// �� �ϴ�
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		// �� ���
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
		// ���̴� ��� + ���̴� ���� �̸�, ������ �Լ� �̸�
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
	// �����Ͷ������� VS�� ���� ������ ���� ���̸� ä���ִ� ������ ���ָ�, ���� �����ϰų� �������� �ʾƵ� �⺻���� �����ϱ� ������,
	// �� �� Ȯ���ϰų� ������ �۾��� �ʿ��� ��� ����� ����ϱ⵵ �Ѵ�.
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		// CullMode == �׸��� ���� �κ� ����
		// D3D11_CULL_BACK == �޸��� ����ڴ�.
		desc.CullMode = D3D11_CULL_BACK;

		// FillMode == ��� ä���� ����
		// D3D11_FILL_SOLID == �� ä��ڴ�.
		// D3D11_FILL_WIREFRAME == �ܰ����� �׸��� // �ȱ׷����� != ����������.
		desc.FillMode = D3D11_FILL_SOLID;

		// �ݽð� �������� �׸��� ����
		desc.FrontCounterClockwise = false;

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
		CHECK(hr);
	}

	// SRV
	// SRV�� �׸��� �����Ͷ�� �� �� �ְ� �׸��� ������ �ִ� �ȼ����� ������ ��� �ִ�.
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

	// ���������� �׸��� �׸��� �ڵ�
	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
	// rect�� �ִ°� �����ͼ� �̸��� �ٲٸ� ��
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
			// �߶��ϰ� ���� �ʴ� == �����
			if (bFall == false)
			{
				// �����ð��� �ʰ��ߴٸ�
				if (uCurJumpT >= maxJumpT)
				{
					uCurJumpT = 0.0f;

					bFall = true;
				}
				else // ������ ��� �ؾ��Ѵٸ�
				{
					curJumpSpd -= maxJumpSpd * Time::Delta();

					position.y += curJumpSpd * 2.0f;

					uCurJumpT += Time::Delta();
				}
			}
			else // bFall == true // �ϰ���
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
	SAFE_RELEASE(srv); // �ѹ� ������ ������ ����ȭ ����
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
