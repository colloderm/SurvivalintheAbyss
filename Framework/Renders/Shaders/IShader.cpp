#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
	ID3DBlob* error = nullptr;

	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),		// 쉐이더 파일 경로
		nullptr,			// 쉐이더 파일의 헤더파일
		nullptr,			// 결과를 내보낼 다른 파일의 포인터
		entryName.c_str(),	// 진입점 이름(실행할 함수 이름)
		profile.c_str(),	// 쉐이더 파일에서 사용할 프로필 이름 (= 쉐이더 버전 이름)
		D3DCOMPILE_ENABLE_STRICTNESS,	// 컴파일 경고 레벨 설정 (얼마나 까다롭게 설정할지)
		0,					// 디버그 정보를 내보낼 파일 생성 위치
		blob,				// 컴파일 결과를 저장할 blob
		&error				// error 메세지를 저장할 blob
	);
	CheckShaderError(hr, error);

	SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
	// HRESULT 결과값이 실패했다고 나올경우
	if (FAILED(hr))
	{
		// 쉐이더를 만드는 도중에 에러가 발생했다면
		if (error)
		{
			// 에러가 발생한 쉐이더의 몇번째 줄에서 어떤 에러가 났는지 확인
			string str = (const char*)error->GetBufferPointer();

			MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
		}
		// 프로그램 폭파
		CHECK(false);
	}
}
