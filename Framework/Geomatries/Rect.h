#pragma once

// 그림이 없는 사각형
class Rect
{
public:
	Rect(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Rect();

	// 매 프레임 마다 실행될 내용들
	// 객체의 데이터의 변화를 실행하는 코드
	void Update();

	// 매 프레임 마다 그림을 그리는 내용
	// 변한 데이터를 가지고 그림을 다시 그리는 코드
	void Render();

	// ImGui를 이용해 UI를 만드는 코드가 들어갈 부분
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
	// 정점의 데이터
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	// 폴리곤을 그릴 순서
	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	// 정점의 데이터 해석 방법
	InputLayout* il = nullptr;

	// 그림을 그릴 쉐이더
	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	// 공간을 명시할 데이터
	WorldBuffer* wb = nullptr;
	Matrix world;	// DirectX가 공간으로 인식할 행렬
	Matrix S, R, T; // 공간에서의 객체의 크기, 회전, 위치 (전역 좌표계)

	Vector3 position;	// 지역 좌표의 위치
	Vector3 size;		// 지역 좌표의 크기
	float rotation;		// 지역 좌표의 회전

	// 색깔 R, G, B, A (A는 사실상 하는게 없음)
	// 0~1까지 밖에 없음 (즉 0 = 0, 1 = 255)
	Color color = Color(1, 0, 0, 1);

	// 이동 제어용 트리거
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

	// 충돌 관련 데이터
	BoundingBox* collision = nullptr;
	RectEdge* edge = nullptr;

	Vector3 verticesLocalPosition[4];

	//float jumpT = 0;
};