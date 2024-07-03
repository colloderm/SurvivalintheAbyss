#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	vpb = new VPBuffer();

	// VPBuffer ����
	{
		D3DXMatrixLookAtLH
		(
			&view,					// ī�޶�
			&Vector3(0, 0, 0),		// ī�޶� ��ġ (���ϴ�)
			&Vector3(0, 0, 1),		// ī�޶� ���� ����
			&Vector3(0, 1, 0)		// ī�޶��� �� // ȸ���� �� ���
		);

		vpb->SetView(view);

		D3DXMatrixOrthoOffCenterLH
		(
			&proj,					// ���� ���� // �þ� ����
			0.0f,					// ���� ��	// x��ǥ �ּ�
			(float)WinMaxWidth,		// ���� ��	// x��ǥ �ִ�
			0.0f,					// �� �Ʒ�	// y��ǥ �ּ�
			(float)WinMaxHeight,	// �� ��		// y��ǥ �ִ�
			0,						// �ּ� ����	// z��ǥ �ּ�
			1						// �ִ� ����	// z��ǥ �ִ�
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
	// Ÿ���� �������
	if (target != nullptr)
	{
		position.x = target->GetPosition().x - WinMaxWidth * 0.5f;
		position.y = target->GetPosition().y - WinMaxHeight * 0.5f;
	}
	else // Ÿ���� ������� // ������ ���
	{
		if (Keyboard::Get()->Down(VK_F2))
		{
			// ���� ��������, ������ ������
			bMove = !bMove;
		}

		if (bMove)
		{
			// ���⼭ ���� ���� Ȯ���ؼ� ���̻� �̵��� �ȵǵ��� �ؾ��ϴµ� ����..
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
	// �ٽ� ����ϱ� ������ �޸𸮰� �������� �ʴ´�.
	D3DXMatrixLookAtLH
	(
		&view,								// ī�޶�
		&position,							// ī�޶� ��ġ (���ϴ�)
		&(position + Vector3(0, 0, 1)),		// ī�޶� ���� ����
		&Vector3(0, 1, 0)					// ī�޶��� �� // ȸ���� �� ���
	);

	vpb->SetView(view);
}

const Vector3 Camera::GetMPosition()
{
	Vector3 Mpos = Mouse::Get()->GetPosition();

	Mpos += position;

	return Mpos;
}
