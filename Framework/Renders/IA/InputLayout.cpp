#include "Framework.h"
#include "InputLayout.h"

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count, ID3DBlob* blob)
{
	// 매개변수 중 하나라도 없다면 폭파
	if (!descs || !count || !blob) CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs,						// 요청서
		count,						// 요소 개수
		blob->GetBufferPointer(),	// 버퍼 위치
		blob->GetBufferSize(),		// 버퍼 크기
		&il
	);
	CHECK(hr);
}

InputLayout::~InputLayout()
{
	SAFE_RELEASE(il);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(il);
}
