#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
	ID3DBlob* error = nullptr;

	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),		// ���̴� ���� ���
		nullptr,			// ���̴� ������ �������
		nullptr,			// ����� ������ �ٸ� ������ ������
		entryName.c_str(),	// ������ �̸�(������ �Լ� �̸�)
		profile.c_str(),	// ���̴� ���Ͽ��� ����� ������ �̸� (= ���̴� ���� �̸�)
		D3DCOMPILE_ENABLE_STRICTNESS,	// ������ ��� ���� ���� (�󸶳� ��ٷӰ� ��������)
		0,					// ����� ������ ������ ���� ���� ��ġ
		blob,				// ������ ����� ������ blob
		&error				// error �޼����� ������ blob
	);
	CheckShaderError(hr, error);

	SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
	// HRESULT ������� �����ߴٰ� ���ð��
	if (FAILED(hr))
	{
		// ���̴��� ����� ���߿� ������ �߻��ߴٸ�
		if (error)
		{
			// ������ �߻��� ���̴��� ���° �ٿ��� � ������ ������ Ȯ��
			string str = (const char*)error->GetBufferPointer();

			MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
		}
		// ���α׷� ����
		CHECK(false);
	}
}
