#pragma once

class IndexBuffer
{
public:
	~IndexBuffer();

	void Create(const vector<UINT>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }

	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	UINT stride = 0;	// 버퍼에서 한 정점의 크기
	UINT offset = 0;	// 버퍼에서 읽을 위치
	UINT count = 0;		// 버퍼에서 읽을 정점의 개수
};