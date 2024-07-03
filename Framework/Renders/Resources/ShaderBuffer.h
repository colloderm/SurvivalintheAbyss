#pragma once
#include "Framework.h"

// CPU에서 GPU로 정점의 데이터가 아닌 데이터를 추가로 건내줄 때 사용할 버퍼

// 생성자가 protected 영역에 있다는것은 외부에서 생성이 불가능하고 자신과 자식만 생성이 가능하기 때문에
// 이는 부모객체로 상속을 하기 위한 객체라는 것을 의미.
class ShaderBuffer
{
public:
	void SetVSBuffer(UINT slot)
	{
		// 데이터 복사
		MapData();
		// VS에게 1개의 Buffer 전달
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(UINT slot)
	{
		// 데이터 복사
		MapData();
		// PS에게 1개의 Buffer 전달
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	// GPU는 정점 이외의 데이터를 받을땐 상수 버퍼를 통해 받는다.
	ShaderBuffer(void* data, UINT dataSize)
		: data(data), dataSize(dataSize)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = dataSize;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}
private:
	// 일반적으로 C++언어에서 map이라 부르는것은 자료형의 일종이지만
	// DirectX에서 map이라고 하는것은 런타임중에 DirectX만 알고 있는 데이터를 접근해 수정 할 수 있도록 하는것을 Mapping이라 한다.
	// Map을 했으면 반드시 UnMap도 해줘야 한다.
	void MapData()
	{
		// 맵하는 동안 데이터를 임시 보관할 구조체
		D3D11_MAPPED_SUBRESOURCE subRe;

		HRESULT hr = DC->Map
		(
			buffer,						// 매핑할 대상
			0,							// 매핑 시작 위치 (0 = 처음부터)
			D3D11_MAP_WRITE_DISCARD,	// 매핑 방법 (WRITE_DISCARD 지우고 다시 써라)
			0,							// 추가로 매핑 할 하위 리소스
			&subRe						// 매핑한 데이터를 저장 할 변수
		);
		CHECK(hr);

		// 데이터복사(이거를, 여기에, 이만큼);
		memcpy(subRe.pData, data, dataSize);

		DC->Unmap(buffer, 0);
	}
private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	// void*는 자료형이 정해져 있지 않은 포인터로, 어떠한 자료형의 데이터도 가리킬 수 있는 포인터이다.
	void* data = nullptr;
	UINT dataSize = 0;
};