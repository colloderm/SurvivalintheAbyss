#pragma once

// IShader는 CPU에서 GPU에게 쉐이더 명령을 내리는 역할
// ShaderBuffer가 건내준 데이터를 IShader가 명령을 내려서 실행한다.
// 어떤 쉐이더 파일에서 어떤 이름의 함수를 실행하라. <- 이거를 주로함
class IShader
{
public:
	// vortual로 선언한 가상함수에 구현부 대신 =0을 넣을 경우
	// 해당 함수는 구현 할 수 없는 순수 가상 함수가 된다.
	// 이러한 순수 가상 함수를 가진 클래스는 함수의 구현부가 존재하지 않기 때문에
	// 해당 클래스만 독자적으로 생성하는 것이 불가능해지고, 
	// 반드시 해당 클래스를 상속받은 자식 클래스가 구현을 해줘야 만들어진다.
	// 자식클래스에서 조차 해당 함수들을 구현하지 않으면 자식 클래스도 생성이 불가능해진다. (중요)

	// 생성
	virtual void Create(const wstring path, const string entryName) = 0;
	// 소멸
	virtual void Clear() = 0;
	// 세팅
	virtual void SetShader() = 0;

protected:
	// 내부에서 포인터를 요구하는 뭔가가 있기에 더블포인터를 사용
	void CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob);

	wstring path = L"";		// 쉐이더 파일 경로
	string entryName = "";	// 진입점 이름(쉐이더 파일에서 실행 할 함수 이름)

private:
	void CheckShaderError(HRESULT hr, ID3DBlob* error);
};