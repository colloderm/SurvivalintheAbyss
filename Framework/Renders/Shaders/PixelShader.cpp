#include "Framework.h"
#include "PixelShader.h"

PixelShader::~PixelShader()
{
	Clear();
}

void PixelShader::Create(const wstring path, const string entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "ps_5_0", &blob);

	HRESULT hr = DEVICE->CreatePixelShader
	(
		blob->GetBufferPointer(),	// 버퍼의 위치
		blob->GetBufferSize(),		// 버퍼의 크기
		nullptr,					// 추가로 연결할 파일
		&shader						// 만든 쉐이더를 집어넣을 쉐이더
	);
	CHECK(hr);
}

void PixelShader::Clear()
{
	SAFE_RELEASE(blob);
	SAFE_RELEASE(shader);
}

void PixelShader::SetShader()
{
	DC->PSSetShader(shader, nullptr, 0);
}
