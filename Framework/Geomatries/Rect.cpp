#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation) //선언 전 데이터를 지정해주는 용도
{
	// Vertices
	{
		vertices.assign(4, VertexColor());

		// 네모 중점(0,0) 기준 // 네모 정점의 각 사이값을 1로 했을경우
		// 좌 하단
		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = color; // Color(0,1,0,1); // 그라데이션사용?

		// 우 상단
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = color;

		// 우 하단
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = color;

		// 좌 상단
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
		// 쉐이더 경로 + 쉐이더 파일 이름, 실행할 함수 이름
		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
		// hlsl은 쉐이더 코드 (확장 프로그램)
		// 빨간줄이 떠도 에러코드는 안나옴
		// 확장프로그램이 있으면 코드 구분도 되고 에러도 알 수 있음.
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
	// 폴리곤을 그리는 방식을 서술
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST는 폴리곤을 그릴때 마지막 변의 방향을 명시하지 않아도 되는 방식
	// 0->1, 1->2, 2->0 == 0,1,2,0 // 원래 이렇게 적어야 하는걸 
	// 0->1, 1->2 == 0,1,2 // 이렇게만 적어도 마지막 2->0 가는 번호는 자동으로 계산하는 방식
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	wb->SetVSBuffer(0);

	ps->SetShader();

	// 최종적으로 그림을 그리는 코드
	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::GUI()
{
	// ImGui를 이용해 UI를 만들어내는 기능과 코드들 (ImGui는 (언리얼/유니티)엔진에서도 유용하게 사용)

	// ImGui 코드를 이용해서 UI를 만들때 먼저 실행해야 하는 함수
	// Begin을 실행하고 중괄호 열어서 함수 찍고
	// End로 닫아 줘야함. 닫지 않으면 에러가 뜸
	ImGui::Begin("Rect");
	{
		// Text는 문자 그대로 문장 하나 출력하는 기능
		ImGui::Text(MakeLabel("Rect").c_str());

		// SilderFloat2는 x, y까지의 데이터를 드래그로 수정 할 수 있게 함
		ImGui::SliderFloat2(MakeLabel("Pos").c_str(), position, 0, WinMaxWidth);
		ImGui::SliderFloat2(MakeLabel("Size").c_str(), size, 0, WinMaxWidth);
		// SliderAngle은 각도 바꿔주는 데이터
		// Degree <- 각도 값 90도를 Radian으로 변환해서 넣어줌
		// rotation은 라디안 값을 입력받음
		ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation, 0, 360);

		// if안에 ImGui코드를 넣을경우 해당 UI를 조작할 때 해당 if문이 True가 된다.
		if (ImGui::ColorPicker3(MakeLabel("Color").c_str(), color))
		{
			// ColorPicker3는 색깔 고르는 팔레트를 RGB까지만 적용
			UpdateColor();
		}
	}
	ImGui::End();
}

void Rect::UpdateWorld()
{
	// 지역 좌표계 즉 로컬 좌표를 글로벌 좌표로 변환하는 과정
	
	// 로컬 좌표의 크기를 글로벌 좌표의 크기로 변경
	D3DXMatrixScaling(&S, size.x, size.y, size.z);

	// 로컬 회전값을 글로벌 회전값으로 변경
	// 이때 받는 데이터가 라디안
	D3DXMatrixRotationZ(&R, rotation); //Z축 기준

	// 로컬 좌표의 위치를 글로벌 좌표의 위치로 변경
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	// SRT 순서로 곱해야함. DirectX가 지정함
	world = S * R * T;
	wb->SetWorld(world);

	collision->UpdateCollisionData(world, verticesLocalPosition);
}

void Rect::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subRe;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
	{
		// 반복문을 사용할 때 (int i = 0; i < n; i++) 의 형식으로 적지 않고
		// 뽑아낼 데이터의 (자료형 + 임시 이름 : 뽑아낼 위치) 의 형식으로 적을 경우
		// 뽑아낼 변수의 안에 있는 모든 데이터를 봅아낼 데이터의 자료형 형식으로 받아온 뒤 임시 이름을 부여해 모든 데이터를 둘러본다.
		// Ex) 아래의 방식을 해석하면
		// Vertices 변수 안에 있는 모든 데이터를 VertexColor&형태로 받아온 뒤
		// v라는 이름을 하나하나 붙이면서 모든 데이터를 확인 할 동안 반복한다.
		// 이러한 반복문을 범위 기반 for문 이라고 부른다. (결과값은 자료형을 따른다)
		// 뒤에 잇는 데이터를 앞에 있는 데이터 형식으로 바꾼다. // 특정조건의 결과값을 뽑아낼 때는 어울리지 않음.
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
	// 자기 자신의 주소를 이용해 고유한 번호와 이름을 만드는 함수

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
//		//위
//		position.y += mSpd * Time::Delta();
//
//		if (Keyboard::Get()->Press('S') && moveD == false)
//		{
//			position.y -= (mSpd * 2) * Time::Delta();
//		}
//	}
//	else if (Keyboard::Get()->Press('S'))
//	{
//		//아래
//		position.y -= mSpd * Time::Delta();
//		moveD = true;
//	}
//
//	if (Keyboard::Get()->Up('S')) moveD = false; //S키를 뗏다면(Up)
//
//	if (Keyboard::Get()->Press('A'))
//	{
//		// 왼쪽
//		position.x -= mSpd * Time::Delta();
//		if (Keyboard::Get()->Press('D') && moveR == false)
//		{
//			position.x += (mSpd * 2) * Time::Delta();
//		}
//	}
//	else if (Keyboard::Get()->Press('D'))
//	{
//		// 오른쪽
//		position.x += mSpd * Time::Delta();
//		moveR = true;
//	}
//
//	if (Keyboard::Get()->Up('D')) moveR = false; //D키를 뗏다면(Up)
//
//	if (Keyboard::Get()->Down(VK_SPACE) && jumpCount < 2) // 연속점프일 때 시간은 안줘도 될..듯?
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
//		// 점프 만들기
//		/*
//		모든 점프는 기본적으로 bool 값을 이용해 특정 키가 눌렸을 때 
//		해당 bool값을 true로 바꾸며 해당 bool값이 true일 때 점프를 실행하는 것을 기본으로 둔다.
//
//		만약, 점프를 누르고 있는 동안 점프의 높이가 점점 증가하는 방식의 점프를 만들고 싶다면 bool값을 사용하지 않아도 된다. // 과제아님
//
//		점프를 만드는법 
//		1. 점프 시간 이용하기 // 일정한 시간의 점프 구현 가능
//		1) 특정 키를 눌렀을 경우 일정 시간동안 위로 간다. (Time::Delta를 계속 특정 변수에 더하다가 해당 변수의 값이 1이 넘엇다면 1초가 지난것)
//		2) 일정 시간이 지난 후 다시 일정 시간동안 내려온다.
//
//		2. 중력 이용하기 // 감속 가속이 있는 점프 구현 가능
//		1) 특정 키를 눌렀을 경우 중력변수 값 만큼 이동을 시작
//		2) 시간이 지남에 따라 지속적으로 중력변수의 값을 - 시킨다.
//		3) 일정 시간이 지나면 중력변수의 값은 결국 음수로 바뀌며 아래로 내려갈 것이다.
//
//		3. 특정 거리까지 이동하기 // 목적지 도달이 쉬운 점프 구현 가능
//		1) 특정 키를 눌렀을 때 이동할 위치 결정
//		2) 해당 위치에 도달할 때 까지 이동
//		3) 해당 위치 도달 후 다시 원래 위치로 이동
//		*/
//	}
//
//	if (bJump)
//	{
//		// 추락하고 있지 않다 == 상승중
//		if (bFall == false)
//		{
//			// 점프시간이 초과했다면
//			if(uCurJumpT >= maxJumpT)
//			{
//				uCurJumpT = 0.0f;
//				bFall = true;
//			}
//			else // 점프를 계속 해야한다면
//			{
//				curJumpSpd -= maxJumpSpd * Time::Delta();
//				position.y += curJumpSpd;
//				uCurJumpT += Time::Delta();
//			}
//		}
//		else // bFall == true // 하강중
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
