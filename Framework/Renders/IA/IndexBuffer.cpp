#include "Framework.h"
#include "IndexBuffer.h"

void IndexBuffer::Create(const vector<UINT>& indices, const D3D11_USAGE& usage)
{
	stride = sizeof(UINT);
	count = indices.size();

	// DESC는 DirectX가 만드는 데이터들을 프로그래머가 '~~만들어 주세요'라고 요청하는 설계도&요청서.
	D3D11_BUFFER_DESC desc; // 구조체(struct)
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	// desc 설정
	{
		// 사용 용도
		desc.Usage = usage;
		// 사용 목적
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		// 버퍼 크기
		desc.ByteWidth = stride * count;

		// cpu 설정
		switch (usage)
		{
			// CPU가 접근할 수 없는 데이터를 가진 버퍼
			// GPU가 접근할 수 있는 데이터를 가진 버퍼
		case D3D11_USAGE_DEFAULT:
			// CPU가 접근할 수 없는 데이터를 가진 버퍼
			// GPU가 접근할 수 없는 데이터를 가진 버퍼
		case D3D11_USAGE_IMMUTABLE:
			break;
			// CPU가 접근할 수 있고 수정할 수 있는 데이터를 가진 버퍼
			// GPU가 접근할 수 없는 데이터를 가진 버퍼
		case D3D11_USAGE_DYNAMIC:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;
			// CPU가 접근할 수 있고 수정할 수 있는 데이터를 가진 버퍼
			// GPU가 접근할 수 있고 데이터를 가진 버퍼
		case D3D11_USAGE_STAGING:
			desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;
		}
	}

	// CreateBuffer
	{
		// D3D11_SUBRESOURCE_DATA는 다양한 데이터들을 임시로 보관할 수 있는 구조체.
		D3D11_SUBRESOURCE_DATA subRe;
		ZeroMemory(&subRe, sizeof(D3D11_SUBRESOURCE_DATA));

		subRe.pSysMem = indices.data();

		// HRESULT는 해당 작업이 정상적으로 수행됐는지 판단하는 기능이며,
		// 작업이 끝난 변수를 CHECK에 집어넣어 만약, 작업이 정상적으로 끝나지 않았다면 프로그램을 폭파시키면서 에러메세지는 출력한다.
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subRe, &buffer); //desc형태의 subRe내용을 buffer에 넣는다.
		CHECK(hr);
	}
}

IndexBuffer::~IndexBuffer()
{
	SAFE_RELEASE(buffer);
}


void IndexBuffer::SetIA()
{
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
