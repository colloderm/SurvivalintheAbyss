#include "Framework.h"
#include "IndexBuffer.h"

void IndexBuffer::Create(const vector<UINT>& indices, const D3D11_USAGE& usage)
{
	stride = sizeof(UINT);
	count = indices.size();

	// DESC�� DirectX�� ����� �����͵��� ���α׷��Ӱ� '~~����� �ּ���'��� ��û�ϴ� ���赵&��û��.
	D3D11_BUFFER_DESC desc; // ����ü(struct)
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	// desc ����
	{
		// ��� �뵵
		desc.Usage = usage;
		// ��� ����
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
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

		subRe.pSysMem = indices.data();

		// HRESULT�� �ش� �۾��� ���������� ����ƴ��� �Ǵ��ϴ� ����̸�,
		// �۾��� ���� ������ CHECK�� ����־� ����, �۾��� ���������� ������ �ʾҴٸ� ���α׷��� ���Ľ�Ű�鼭 �����޼����� ����Ѵ�.
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subRe, &buffer); //desc������ subRe������ buffer�� �ִ´�.
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
