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

void TextureRect::MoveAction(int type, float move)
{
	float mSpd = 20.0f;

	if (type == 1)
	{
		position.x += move * mSpd * Time::Delta();
	}
	else if (type == 2)
	{
		position.x -= move * mSpd * Time::Delta();
	}

	if (type == 4)
	{
		position.y += move * mSpd * Time::Delta();
	}
	else if (type == 5)
	{
		position.y -= move * mSpd * Time::Delta();
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
