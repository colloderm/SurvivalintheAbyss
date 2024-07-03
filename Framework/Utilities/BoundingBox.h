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
	Vector3 centerPos;	// �߾� ��ǥ
	Vector3 axisDir[2]; // �� ����
	float axisLen[2];	// �� ����
};

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	void UpdateCollisionData(const Matrix world, const Vector3 verticesLocalPosition[]); // �𼭸��� ������ǥ��

	// static Ű����
	// - Ŭ������ ���� ���� �ش� Ŭ������ ������ �ִ� �Լ���, ������ ����� �� �ְ� ���ִ� Ű����
	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b);

private:
	RectEdge* edge = nullptr;
	AxisData* data = nullptr;
};