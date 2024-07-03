#pragma once

class VertexBuffer //cpu���� gpu�� �ǳ��ִ� ����
{
public:
	~VertexBuffer();

	// template<typename T>�� �� ������ ���� �Լ��� ���� T�� ��� ���� ����� �� �ֵ��� ���ִ� ���.
	// Create���� ���ø� ����ϴ� ������ �׸� �簢���� ���� �ٸ� ���� �����͸� �ǳ���� �ϱ� �����̴�.
	template<typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }

	UINT GetStride()	 { return stride; }
	UINT GetOffset()	 { return offset; }
	UINT GetCount()		 { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	UINT stride = 0;	// ���ۿ��� �� ������ ũ��
	UINT offset = 0;	// ���ۿ��� ���� ��ġ
	UINT count = 0;		// ���ۿ��� ���� ������ ����
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);
	count = vertices.size();

	// DESC�� DirectX�� ����� �����͵��� ���α׷��Ӱ� '~~����� �ּ���'��� ��û�ϴ� ���赵&��û��.
	D3D11_BUFFER_DESC desc; // ����ü(struct)
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	// desc ����
	{
		// ��� �뵵
		desc.Usage = usage;
		// ��� ����
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// ���� ũ��
		desc.ByteWidth = stride * count;

		// cpu ����
		switch (usage)
		{
			// CPU�� ������ �� ���� �����͸� ���� ����
			// GPU�� ������ �� �ִ� �����͸� ���� ����
		case D3D11_USAGE_DEFAULT:
			// CPU�� ������ �� ���� �����͸� ���� ����
			// GPU�� ������ �� ���� �����͸� ���� ����
		case D3D11_USAGE_IMMUTABLE:
			break;
			// CPU�� ������ �� �ְ� ������ �� �ִ� �����͸� ���� ����
			// GPU�� ������ �� ���� �����͸� ���� ����
		case D3D11_USAGE_DYNAMIC:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;
			// CPU�� ������ �� �ְ� ������ �� �ִ� �����͸� ���� ����
			// GPU�� ������ �� �ְ� �����͸� ���� ����
		case D3D11_USAGE_STAGING:
			desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;
		}
	}

	// CreateBuffer
	{
		// D3D11_SUBRESOURCE_DATA�� �پ��� �����͵��� �ӽ÷� ������ �� �ִ� ����ü.
		D3D11_SUBRESOURCE_DATA subRe;
		ZeroMemory(&subRe, sizeof(D3D11_SUBRESOURCE_DATA));

		subRe.pSysMem = vertices.data();

		// HRESULT�� �ش� �۾��� ���������� ����ƴ��� �Ǵ��ϴ� ����̸�,
		// �۾��� ���� ������ CHECK�� ����־� ����, �۾��� ���������� ������ �ʾҴٸ� ���α׷��� ���Ľ�Ű�鼭 �����޼����� ����Ѵ�.
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subRe, &buffer); //desc������ subRe������ buffer�� �ִ´�.
		CHECK(hr);
	}
}
