#pragma once

enum
{
	x = 0,
	y
};

struct RectEdge //AABB
{
	Vector3 LT;
	Vector3 RT;
	Vector3 LB;
	Vector3 RB;
};

struct AxisData //OBB
{
	Vector3 centerPos;	// 중앙 좌표
	Vector3 axisDir[2]; // 축 방향
	float axisLen[2];	// 축 길이
};

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	void UpdateCollisionData(const Matrix world, const Vector3 verticesLocalPosition[]); // 모서리의 지역좌표계

	// static 키워드
	// - 클래스의 구현 없이 해당 클래스가 가지고 있는 함수나, 변수를 사용할 수 있게 해주는 키워드
	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b);

private:
	RectEdge* edge = nullptr;
	AxisData* data = nullptr;
};