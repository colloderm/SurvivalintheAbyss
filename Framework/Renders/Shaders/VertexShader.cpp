#include "Framework.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
	Clear(); // �ڵ����� ���Ǳ� ���� Ŭ���� ���
}

void VertexShader::Create(const wstring path, const string entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "vs_5_0", &blob); // vs_5_0�� ����

	HRESULT hr = DEVICE->CreateVertexShader
	(
		blob->GetBufferPointer(),	// ������ ��ġ
		blob->GetBufferSize(),		// ������ ũ��
		nullptr,					// �߰��� ������ ����
		&shader						// ���� ���̴��� ������� ���̴�
	);
	CHECK(hr);
}

void VertexShader::Clear()
{
	SAFE_RELEASE(blob);
	SAFE_RELEASE(shader);
}

void VertexShader::SetShader()
{
	DC->VSSetShader(shader, nullptr, 0);
}
