#include "Framework.h"
#include "InputLayout.h"

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count, ID3DBlob* blob)
{
	// �Ű����� �� �ϳ��� ���ٸ� ����
	if (!descs || !count || !blob) CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs,						// ��û��
		count,						// ��� ����
		blob->GetBufferPointer(),	// ���� ��ġ
		blob->GetBufferSize(),		// ���� ũ��
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
