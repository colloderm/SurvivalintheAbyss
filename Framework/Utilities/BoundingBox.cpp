#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	edge = new RectEdge();
	data = new AxisData();
}

BoundingBox::~BoundingBox()
{
	SAFE_DELETE(data);
	SAFE_DELETE(edge);
}

void BoundingBox::UpdateCollisionData(const Matrix world, const Vector3 verticesLocalPosition[])
{
	// AABB // RectEdge
	{
		D3DXVec3TransformCoord(&edge->LT, &verticesLocalPosition[3], &world);
		D3DXVec3TransformCoord(&edge->LB, &verticesLocalPosition[0], &world);
		D3DXVec3TransformCoord(&edge->RT, &verticesLocalPosition[1], &world);
		D3DXVec3TransformCoord(&edge->RB, &verticesLocalPosition[2], &world);
	}

	// OBB // AxisData
	{
		// CenterPos // 사각형 중심 위치
		{
			data->centerPos = Vector3
			(
				(edge->LT.x + edge->RT.x + edge->LB.x + edge->RB.x) * 0.25f,
				(edge->LT.y + edge->RT.y + edge->LB.y + edge->RB.y) * 0.25f,
				0
			);
		}

		// AxisDir // 축 방향
		{
			// 정규화(normalize)
			// - 모든 값을 0~1로 바궈주는 과정
			// 글로벌 좌표
			D3DXVec3TransformNormal(&data->axisDir[x], &Vector3(1, 0, 0), &world); // RightVector	// 사각형 오른쪽
			D3DXVec3TransformNormal(&data->axisDir[y], &Vector3(0, 1, 0), &world); // UpVector		// 사각형 위쪽

			// 지역좌표로 변경
			D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
			D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
		}

		// AxisLen // 축 길이
		{
			Vector3 axisDir[2] = { data->axisDir[x], data->axisDir[y] };
			Vector3 verticesPos[4] = { edge->LT, edge->RT, edge->LB, edge->RB };

			float minValues[2] = { INT_MAX, INT_MAX };
			float maxValues[2] = { INT_MIN, INT_MIN };

			for (int i = 0; i < 4; i++)
			{
				Vector3 point = verticesPos[i];

				for (int j = 0; j < 2; j++)
				{
					float projection = D3DXVec3Dot(&point, &axisDir[j]);

					// 네모가 가지고 있는 x, y 최소값 찾기
					if (projection < minValues[j])
						minValues[j] = projection;

					// 네모가 가지고 있는 x, y 최대값 찾기
					if (projection > maxValues[j])
						maxValues[j] = projection;
				}
			}

			data->axisLen[x] = (maxValues[x] - minValues[x]) * 0.5f; // x반지름
			data->axisLen[y] = (maxValues[y] - minValues[y]) * 0.5f; // y반지름
		}
	}
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	if (a == nullptr || b == nullptr) return false;

	RectEdge aEdge = *a->edge;
	RectEdge bEdge = *b->edge;

	// 회전하지 않은 사각형들의 충돌에서 두 사각형이 충돌했다를 판정하기 위해서는
	// 각각 사각형이 가지고 있는 가장 크고 작은 x, y값들이 큰 값은 커야하고 작은 값은 작아야 한다.
	if (aEdge.LT.x <= bEdge.RB.x && 
		aEdge.LT.y >= bEdge.RB.y && 
		aEdge.RB.x >= bEdge.LT.x && 
		aEdge.RB.y <= bEdge.LT.y)
		return true;

	return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
	if (a == nullptr || b == nullptr) return false;

	AxisData ad = *a->data;
	AxisData bd = *b->data;

	Vector3 centerDir, axis;
	float centerProjDist, r1, r2;

	// a와 b사이의 거리
	centerDir = ad.centerPos - bd.centerPos;

	// a Rect : X축
	{
		// 축 설정
		axis = ad.axisDir[x];

		// 비교할 사이 거리
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		// aRect의 x축 이기 때문에 ad의 len[x]
		r1 = ad.axisLen[x];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) + 
			abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2) return false; // 충돌 x
	}

	// a Rect : Y축
	{
		axis = ad.axisDir[y];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[y];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
			abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2) return false;
	}

	// b Rect : X축
	{
		axis = bd.axisDir[x];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[x];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2) return false;
	}

	// b Rect : Y축
	{
		axis = bd.axisDir[y];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[y];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2) return false;
	}

	return true;
}
