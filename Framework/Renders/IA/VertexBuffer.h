#pragma once

class VertexBuffer //cpu에서 gpu로 건내주는 상자
{
public:
	~VertexBuffer();

	// template<typename T>는 이 다음에 오는 함수에 들어가는 T를 어떤게 들어가든 사용할 수 있도록 해주는 기능.
	// Create에서 템플릿 사용하는 이유는 그릴 사각형에 따라 다른 정점 데이터를 건내줘야 하기 때문이다.
	template<typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }

	UINT GetStride()	 { return stride; }
	UINT GetOffset()	 { return offset; }
	UINT GetCount()		 { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	UINT stride = 0;	// 버퍼에서 한 정점의 크기
	UINT offset = 0;	// 버퍼에서 읽을 위치
	UINT count = 0;		// 버퍼에서 읽을 정점의 개수
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);
	count = vertices.size();

	// DESC는 DirectX가 만드는 데이터들을 프로그래머가 '~~만들어 주세요'라고 요청하는 설계도&요청서.
	D3D11_BUFFER_DESC desc; // 구조체(struct)
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	// desc 설정
	{
		// 사용 용도
		desc.Usage = usage;
		// 사용 목적
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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

		subRe.pSysMem = vertices.data();

		// HRESULT는 해당 작업이 정상적으로 수행됐는지 판단하는 기능이며,
		// 작업이 끝난 변수를 CHECK에 집어넣어 만약, 작업이 정상적으로 끝나지 않았다면 프로그램을 폭파시키면서 에러메세지는 출력한다.
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subRe, &buffer); //desc형태의 subRe내용을 buffer에 넣는다.
		CHECK(hr);
	}
}
