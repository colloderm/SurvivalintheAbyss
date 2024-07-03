#pragma once
#include "Framework.h"

// CPU���� GPU�� ������ �����Ͱ� �ƴ� �����͸� �߰��� �ǳ��� �� ����� ����

// �����ڰ� protected ������ �ִٴ°��� �ܺο��� ������ �Ұ����ϰ� �ڽŰ� �ڽĸ� ������ �����ϱ� ������
// �̴� �θ�ü�� ����� �ϱ� ���� ��ü��� ���� �ǹ�.
class ShaderBuffer
{
public:
	void SetVSBuffer(UINT slot)
	{
		// ������ ����
		MapData();
		// VS���� 1���� Buffer ����
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(UINT slot)
	{
		// ������ ����
		MapData();
		// PS���� 1���� Buffer ����
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	// GPU�� ���� �̿��� �����͸� ������ ��� ���۸� ���� �޴´�.
	ShaderBuffer(void* data, UINT dataSize)
		: data(data), dataSize(dataSize)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = dataSize;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //�������
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}
private:
	// �Ϲ������� C++���� map�̶� �θ��°��� �ڷ����� ����������
	// DirectX���� map�̶�� �ϴ°��� ��Ÿ���߿� DirectX�� �˰� �ִ� �����͸� ������ ���� �� �� �ֵ��� �ϴ°��� Mapping�̶� �Ѵ�.
	// Map�� ������ �ݵ�� UnMap�� ����� �Ѵ�.
	void MapData()
	{
		// ���ϴ� ���� �����͸� �ӽ� ������ ����ü
		D3D11_MAPPED_SUBRESOURCE subRe;

		HRESULT hr = DC->Map
		(
			buffer,						// ������ ���
			0,							// ���� ���� ��ġ (0 = ó������)
			D3D11_MAP_WRITE_DISCARD,	// ���� ��� (WRITE_DISCARD ����� �ٽ� ���)
			0,							// �߰��� ���� �� ���� ���ҽ�
			&subRe						// ������ �����͸� ���� �� ����
		);
		CHECK(hr);

		// �����ͺ���(�̰Ÿ�, ���⿡, �̸�ŭ);
		memcpy(subRe.pData, data, dataSize);

		DC->Unmap(buffer, 0);
	}
private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	// void*�� �ڷ����� ������ ���� ���� �����ͷ�, ��� �ڷ����� �����͵� ����ų �� �ִ� �������̴�.
	void* data = nullptr;
	UINT dataSize = 0;
};