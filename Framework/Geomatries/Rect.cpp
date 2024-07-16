#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation) //���� �� �����͸� �������ִ� �뵵
{
	// Vertices
	{
		vertices.assign(4, VertexColor());

		// �׸� ����(0,0) ���� // �׸� ������ �� ���̰��� 1�� �������
		// �� �ϴ�
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = color; // Color(0,1,0,1); // �׶��̼ǻ��?

		// �� ���
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = color;

		// �� �ϴ�
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = color;

		// �� ���
		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].color = color;
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
		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
		// hlsl�� ���̴� �ڵ� (Ȯ�� ���α׷�)
		// �������� ���� �����ڵ�� �ȳ���
		// Ȯ�����α׷��� ������ �ڵ� ���е� �ǰ� ������ �� �� ����.
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
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

Rect::~Rect()
{
	SAFE_DELETE(edge);
	SAFE_DELETE(collision);

	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void Rect::Update()
{
	UpdateWorld();
}

void Rect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	// �������� �׸��� ����� ����
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST�� �������� �׸��� ������ ���� ������ ������� �ʾƵ� �Ǵ� ���
	// 0->1, 1->2, 2->0 == 0,1,2,0 // ���� �̷��� ����� �ϴ°� 
	// 0->1, 1->2 == 0,1,2 // �̷��Ը� ��� ������ 2->0 ���� ��ȣ�� �ڵ����� ����ϴ� ���
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	wb->SetVSBuffer(0);

	ps->SetShader();

	// ���������� �׸��� �׸��� �ڵ�
	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::GUI()
{
	// ImGui�� �̿��� UI�� ������ ��ɰ� �ڵ�� (ImGui�� (�𸮾�/����Ƽ)���������� �����ϰ� ���)

	// ImGui �ڵ带 �̿��ؼ� UI�� ���鶧 ���� �����ؾ� �ϴ� �Լ�
	// Begin�� �����ϰ� �߰�ȣ ��� �Լ� ���
	// End�� �ݾ� �����. ���� ������ ������ ��
	ImGui::Begin("Rect");
	{
		// Text�� ���� �״�� ���� �ϳ� ����ϴ� ���
		ImGui::Text(MakeLabel("Rect").c_str());

		// SilderFloat2�� x, y������ �����͸� �巡�׷� ���� �� �� �ְ� ��
		ImGui::SliderFloat2(MakeLabel("Pos").c_str(), position, 0, WinMaxWidth);
		ImGui::SliderFloat2(MakeLabel("Size").c_str(), size, 0, WinMaxWidth);
		// SliderAngle�� ���� �ٲ��ִ� ������
		// Degree <- ���� �� 90���� Radian���� ��ȯ�ؼ� �־���
		// rotation�� ���� ���� �Է¹���
		ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation, 0, 360);

		// if�ȿ� ImGui�ڵ带 ������� �ش� UI�� ������ �� �ش� if���� True�� �ȴ�.
		if (ImGui::ColorPicker3(MakeLabel("Color").c_str(), color))
		{
			// ColorPicker3�� ���� ���� �ȷ�Ʈ�� RGB������ ����
			UpdateColor();
		}
	}
	ImGui::End();
}

void Rect::UpdateWorld()
{
	// ���� ��ǥ�� �� ���� ��ǥ�� �۷ι� ��ǥ�� ��ȯ�ϴ� ����
	
	// ���� ��ǥ�� ũ�⸦ �۷ι� ��ǥ�� ũ��� ����
	D3DXMatrixScaling(&S, size.x, size.y, size.z);

	// ���� ȸ������ �۷ι� ȸ�������� ����
	// �̶� �޴� �����Ͱ� ����
	D3DXMatrixRotationZ(&R, rotation); //Z�� ����

	// ���� ��ǥ�� ��ġ�� �۷ι� ��ǥ�� ��ġ�� ����
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	// SRT ������ ���ؾ���. DirectX�� ������
	world = S * R * T;
	wb->SetWorld(world);

	collision->UpdateCollisionData(world, verticesLocalPosition);
}

void Rect::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subRe;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
	{
		// �ݺ����� ����� �� (int i = 0; i < n; i++) �� �������� ���� �ʰ�
		// �̾Ƴ� �������� (�ڷ��� + �ӽ� �̸� : �̾Ƴ� ��ġ) �� �������� ���� ���
		// �̾Ƴ� ������ �ȿ� �ִ� ��� �����͸� ���Ƴ� �������� �ڷ��� �������� �޾ƿ� �� �ӽ� �̸��� �ο��� ��� �����͸� �ѷ�����.
		// Ex) �Ʒ��� ����� �ؼ��ϸ�
		// Vertices ���� �ȿ� �ִ� ��� �����͸� VertexColor&���·� �޾ƿ� ��
		// v��� �̸��� �ϳ��ϳ� ���̸鼭 ��� �����͸� Ȯ�� �� ���� �ݺ��Ѵ�.
		// �̷��� �ݺ����� ���� ��� for�� �̶�� �θ���. (������� �ڷ����� ������)
		// �ڿ� �մ� �����͸� �տ� �ִ� ������ �������� �ٲ۴�. // Ư�������� ������� �̾Ƴ� ���� ��︮�� ����.
		for (VertexColor& v : vertices)
		{
			v.color = color;
		}

		memcpy(subRe.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);
}

void Rect::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}

string Rect::MakeLabel(string label)
{
	// �ڱ� �ڽ��� �ּҸ� �̿��� ������ ��ȣ�� �̸��� ����� �Լ�

	string Label = label + "##" + to_string((uint)this);
	return Label;
}

void Rect::MoveAction(int type, float move)
{
	if (type == 0)
	{
		position.x += move * 20.0f * Time::Delta();
	}
	else if (type == 1)
	{
		position.x -= move * 20.0f * Time::Delta();
	}

	if (type == 2)
	{
		position.y += move * 20.0f * Time::Delta();
	}
	else if (type == 3)
	{
		position.y -= move * 20.0f * Time::Delta();
	}
}

//void Rect::Move()
//{
//	float mSpd = 100.0f;
//
//	if (Keyboard::Get()->Press('W'))
//	{
//		//��
//		position.y += mSpd * Time::Delta();
//
//		if (Keyboard::Get()->Press('S') && moveD == false)
//		{
//			position.y -= (mSpd * 2) * Time::Delta();
//		}
//	}
//	else if (Keyboard::Get()->Press('S'))
//	{
//		//�Ʒ�
//		position.y -= mSpd * Time::Delta();
//		moveD = true;
//	}
//
//	if (Keyboard::Get()->Up('S')) moveD = false; //SŰ�� �´ٸ�(Up)
//
//	if (Keyboard::Get()->Press('A'))
//	{
//		// ����
//		position.x -= mSpd * Time::Delta();
//		if (Keyboard::Get()->Press('D') && moveR == false)
//		{
//			position.x += (mSpd * 2) * Time::Delta();
//		}
//	}
//	else if (Keyboard::Get()->Press('D'))
//	{
//		// ������
//		position.x += mSpd * Time::Delta();
//		moveR = true;
//	}
//
//	if (Keyboard::Get()->Up('D')) moveR = false; //DŰ�� �´ٸ�(Up)
//
//	if (Keyboard::Get()->Down(VK_SPACE) && jumpCount < 2) // ���������� �� �ð��� ���൵ ��..��?
//	{
//		bJump = true;
//		if (jumpCount == 0) jumpStartY = position.y;
//		else if (jumpCount > 0)
//		{
//			uCurJumpT = 0;
//			dCurJumpT = 0 - (maxJumpT - dCurJumpT);
//			curJumpSpd = maxJumpSpd;
//			bFall = false;
//		}
//		jumpCount++;
//		
//		// ���� �����
//		/*
//		��� ������ �⺻������ bool ���� �̿��� Ư�� Ű�� ������ �� 
//		�ش� bool���� true�� �ٲٸ� �ش� bool���� true�� �� ������ �����ϴ� ���� �⺻���� �д�.
//
//		����, ������ ������ �ִ� ���� ������ ���̰� ���� �����ϴ� ����� ������ ����� �ʹٸ� bool���� ������� �ʾƵ� �ȴ�. // �����ƴ�
//
//		������ ����¹� 
//		1. ���� �ð� �̿��ϱ� // ������ �ð��� ���� ���� ����
//		1) Ư�� Ű�� ������ ��� ���� �ð����� ���� ����. (Time::Delta�� ��� Ư�� ������ ���ϴٰ� �ش� ������ ���� 1�� �Ѿ��ٸ� 1�ʰ� ������)
//		2) ���� �ð��� ���� �� �ٽ� ���� �ð����� �����´�.
//
//		2. �߷� �̿��ϱ� // ���� ������ �ִ� ���� ���� ����
//		1) Ư�� Ű�� ������ ��� �߷º��� �� ��ŭ �̵��� ����
//		2) �ð��� ������ ���� ���������� �߷º����� ���� - ��Ų��.
//		3) ���� �ð��� ������ �߷º����� ���� �ᱹ ������ �ٲ�� �Ʒ��� ������ ���̴�.
//
//		3. Ư�� �Ÿ����� �̵��ϱ� // ������ ������ ���� ���� ���� ����
//		1) Ư�� Ű�� ������ �� �̵��� ��ġ ����
//		2) �ش� ��ġ�� ������ �� ���� �̵�
//		3) �ش� ��ġ ���� �� �ٽ� ���� ��ġ�� �̵�
//		*/
//	}
//
//	if (bJump)
//	{
//		// �߶��ϰ� ���� �ʴ� == �����
//		if (bFall == false)
//		{
//			// �����ð��� �ʰ��ߴٸ�
//			if(uCurJumpT >= maxJumpT)
//			{
//				uCurJumpT = 0.0f;
//				bFall = true;
//			}
//			else // ������ ��� �ؾ��Ѵٸ�
//			{
//				curJumpSpd -= maxJumpSpd * Time::Delta();
//				position.y += curJumpSpd;
//				uCurJumpT += Time::Delta();
//			}
//		}
//		else // bFall == true // �ϰ���
//		{
//			if (dCurJumpT >= maxJumpT)
//			{
//				curJumpSpd = maxJumpSpd;
//				dCurJumpT = 0.0f;
//				position.y = jumpStartY;
//				jumpCount = 0;
//
//				bJump = false;
//				bFall = false;
//			}
//			else
//			{
//				curJumpSpd += maxJumpSpd * Time::Delta();
//				position.y -= curJumpSpd;
//				if (position.y <= jumpStartY)
//				{
//					position.y = jumpStartY;
//					dCurJumpT = maxJumpT;
//				}
//				dCurJumpT += Time::Delta();
//			}
//		}
//
//		/*jumpT += Time::Delta();
//		if (jumpT <= 1)
//		{
//			position.y += 200.0f * Time::Delta();
//		}
//		else
//		{
//			position.y -= 200.0f * Time::Delta();
//			if (jumpT >= 2)
//			{
//				bJump = false;
//				jumpT = 0;
//			}
//		}*/
//	}
//}
//
//void Rect::Move2(int move2Check)
//{
//	if (move2Check == 1)
//	{
//		position.x -= 300.0f * Time::Delta();
//		if (position.x <= -300)
//		{
//			position.x = (float)Random::GetRandomInt(1500, 2500);
//		}
//	}
//}
