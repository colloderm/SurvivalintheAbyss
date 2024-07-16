#pragma once

// �׸��� ���� �簢��
class Rect
{
public:
	Rect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Rect();

	// �� ������ ���� ����� �����
	// ��ü�� �������� ��ȭ�� �����ϴ� �ڵ�
	void Update();

	// �� ������ ���� �׸��� �׸��� ����
	// ���� �����͸� ������ �׸��� �ٽ� �׸��� �ڵ�
	void Render();

	// ImGui�� �̿��� UI�� ����� �ڵ尡 �� �κ�
	void GUI();

	void UpdateWorld();

	void UpdateColor();
	void SetColor(Color color);

	string MakeLabel(string label);

	//void Move();
	//void Move2(int move2Check);
	void MoveAction(int type, float move);

	BoundingBox* GetCollision() { return collision; }

	void SetPosition(Vector3 position) { this->position = position; }
	RectEdge* GetEdge() { return edge; }
	Vector3 GetPosition() { return position; }

private:
	// ������ ������
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	// �������� �׸� ����
	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	// ������ ������ �ؼ� ���
	InputLayout* il = nullptr;

	// �׸��� �׸� ���̴�
	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	// ������ ����� ������
	WorldBuffer* wb = nullptr;
	Matrix world;	// DirectX�� �������� �ν��� ���
	Matrix S, R, T; // ���������� ��ü�� ũ��, ȸ��, ��ġ (���� ��ǥ��)

	Vector3 position;	// ���� ��ǥ�� ��ġ
	Vector3 size;		// ���� ��ǥ�� ũ��
	float rotation;		// ���� ��ǥ�� ȸ��

	// ���� R, G, B, A (A�� ��ǻ� �ϴ°� ����)
	// 0~1���� �ۿ� ���� (�� 0 = 0, 1 = 255)
	Color color = Color(1, 0, 0, 1);

	// �̵� ����� Ʈ����
	bool moveD = false;
	bool moveR = false;
	bool bJump = false;

	float maxJumpT = 1.0f;
	float uCurJumpT = 0.0f;
	float dCurJumpT = 0.0f;

	float maxJumpSpd = 10.0f;
	float curJumpSpd = maxJumpSpd;

	bool bFall = false;

	float jumpStartY = 0.0f;

	int jumpCount = 0;

	// �浹 ���� ������
	BoundingBox* collision = nullptr;
	RectEdge* edge = nullptr;

	Vector3 verticesLocalPosition[4];

	//float jumpT = 0;
};