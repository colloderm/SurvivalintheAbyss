#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	vpb = new VPBuffer();

	// VPBuffer 세팅
	{
		D3DXMatrixLookAtLH
		(
			&view,					// 카메라
			&Vector3(0, 0, 0),		// 카메라 위치 (좌하단)
			&Vector3(0, 0, 1),		// 카메라가 보는 방향
			&Vector3(0, 1, 0)		// 카메라의 위 // 회전할 때 사용
		);

		vpb->SetView(view);

		D3DXMatrixOrthoOffCenterLH
		(
			&proj,					// 투영 범위 // 시야 범위
			0.0f,					// 왼쪽 끝	// x좌표 최소
			(float)WinMaxWidth,		// 오른 끝	// x좌표 최대
			0.0f,					// 맨 아래	// y좌표 최소
			(float)WinMaxHeight,	// 맨 위		// y좌표 최대
			0,						// 최소 깊이	// z좌표 최소
			1						// 최대 깊이	// z좌표 최대
		);

		vpb->SetProj(proj);
	}
}

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}

void Camera::Update()
{
	Move();
	UpdateView();
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move()
{
	// 타겟이 있을경우
	if (target != nullptr)
	{
		position.x = target->GetPosition().x - WinMaxWidth * 0.5f;
		position.y = target->GetPosition().y - WinMaxHeight * 0.5f;
	}
	else // 타겟이 없을경우 // 개발자 모드
	{
		if (Keyboard::Get()->Down(VK_F2))
		{
			// 참은 거짓으로, 거짓은 참으로
			bMove = !bMove;
		}

		if (bMove)
		{
			// 여기서 맵의 끝을 확인해서 더이상 이동이 안되도록 해야하는데 뗴잉..
			if (Keyboard::Get()->Press('W'))
				position.y += moveSpd * Time::Delta();
			else if (Keyboard::Get()->Press('S'))
				position.y -= moveSpd * Time::Delta();

			if (Keyboard::Get()->Press('A'))
				position.x -= moveSpd * Time::Delta();
			else if (Keyboard::Get()->Press('D'))
				position.x += moveSpd * Time::Delta();
		}
	}
}

void Camera::UpdateView()
{
	// 다시 계산하기 때문에 메모리가 증가되지 않는다.
	D3DXMatrixLookAtLH
	(
		&view,								// 카메라
		&position,							// 카메라 위치 (좌하단)
		&(position + Vector3(0, 0, 1)),		// 카메라가 보는 방향
		&Vector3(0, 1, 0)					// 카메라의 위 // 회전할 때 사용
	);

	vpb->SetView(view);
}

const Vector3 Camera::GetMPosition()
{
	Vector3 Mpos = Mouse::Get()->GetPosition();

	Mpos += position;

	return Mpos;
}
