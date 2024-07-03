#pragma once
#include "Framework.h"

/*
WVP는 3D공간과 모델을 2D 스크린 좌표로 변환하는 과정 중 하나이다.
모니터가 2D이기 때문에 3D게임도 2D좌표로 변환 할 필요가 있다.

World // 공간
- 모델의 정점을 글로벌 좌표에서 지역 좌표로 변환하는 것을 의미
- 모델의 위치, 회전, 크기 등을 조정.

View // 카메라
- 글로벌 좌표에서 카메라가 바라보는 방향을 나타냄
// 실제 카메라 객체가 있는건 아님
- 카메라의 위치, 방향, 시야를 조정.

projection // 투영
- 3D공간을 2D 스크린 좌표로 변환시키는 방법
- 시야각, 종횡비, 크리핑 평면(단면도)등을 고려하여 조정.

WVP를 연산하여 DirectX에서 그릴때는 반드시
World * View * Projection의 순서로 곱해야 한다. // DirectX가 그렇게 정함
*/

class WorldBuffer : public ShaderBuffer
{
public:

	WorldBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		// 행렬 초기화
		// 행렬이 가지고 있는 모든 데이터를 0으로 초기화
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(Matrix world)
	{
		// 전치 행렬
		// └> 열과 행이 서로 바뀌는 교환
		// world의 행이 데이터.월드의 열, world의 열이 데이터.월드의 행
		D3DXMatrixTranspose(&data.world, &world);
	}

	// CPU에서 GPU로 넘길 데이터의 구조체
	// 메모리 할당량의 합이 16의 배수의 크기를 할당해주지 않으면 에러가 난다.
	// Ex) int(4Byte) 4개 == 16Byte / char(1Byte) 32개 == 32Byte
	// Ex) 16, 32, 64 ...
	struct Data
	{
		Matrix world; // Matrix = float 16개 == 64Byte(16*4)의 크기가 됨(아무튼 크기됨)
		// 만약에 메모리 할당량이 부족해 사용하지 않을 데이터를 추가로 넣어줄 경우 이러한 데이터를 패딩 데이터라 부른다.
		// int padding // int dummy
	};

private:
	Data data;
};

class VPBuffer : public ShaderBuffer
{
public:

	VPBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.proj);
	}

	void SetView(Matrix view)
	{
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProj(Matrix proj)
	{
		D3DXMatrixTranspose(&data.proj, &proj);
	}

	struct Data
	{
		Matrix view;	// 카메라
		Matrix proj;	// 투영법(시야)
	};

private:
	Data data;
};