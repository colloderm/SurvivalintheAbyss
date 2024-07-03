#include "Framework.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
	Clear(); // 자동으로 사용되기 위해 클리어 사용
}

void VertexShader::Create(const wstring path, const string entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "vs_5_0", &blob); // vs_5_0은 버전

	HRESULT hr = DEVICE->CreateVertexShader
	(
		blob->GetBufferPointer(),	// 버퍼의 위치
		blob->GetBufferSize(),		// 버퍼의 크기
		nullptr,					// 추가로 연결할 파일
		&shader						// 만든 쉐이더를 집어넣을 쉐이더
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
