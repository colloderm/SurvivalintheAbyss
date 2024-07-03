#pragma once

class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation = 0.0f);
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
	~TextureRect();

	// �� ������ ���� ����� �����
	// ��ü�� �������� ��ȭ�� �����ϴ� �ڵ�
	void Update();

	// �� ������ ���� �׸��� �׸��� ����
	// ���� �����͸� ������ �׸��� �ٽ� �׸��� �ڵ�
	void Render();

	// ImGui�� �̿��� UI�� ����� �ڵ尡 �� �κ�
	void GUI();

	void UpdateWorld();

	string MakeLabel(string label);

	void Move(int moveCheck);
	void Move2(int move2Check);

	void SetImage(wstring imagePath);
	void SetShader(wstring shaderPath);

	BoundingBox* GetCollision() { return collision; }

	void SetPosition(Vector3 position) { this->position = position; }
	void SetSize(Vector3 size) { this->size = size; }
	RectEdge* GetEdge() { return edge; }
	Vector3 GetPosition() { return position; }
protected:
	// ������ ������
	vector<VertexTexture> vertices;
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

	ID3D11ShaderResourceView* srv = nullptr;	// �׸��� ������
	ID3D11RasterizerState* rs = nullptr;		// �ȼ� ä��� ����

	// �̵� ����� Ʈ����
	bool moveD = false;
	bool moveR = false;
	bool bJump = false;
	bool bDown = false;

	float maxJumpT = 1.0f;
	float uCurJumpT = 0.0f;
	float dCurJumpT = 0.0f;

	float maxJumpSpd = 2.0f;
	float curJumpSpd = maxJumpSpd;

	bool bFall = false;

	float jumpStartY = 0.0f;

	int jumpCount = 0;

	// �浹 ���� ������
	BoundingBox* collision = nullptr;
	RectEdge* edge = nullptr;
	Vector3 verticesLocalPosition[4];
};