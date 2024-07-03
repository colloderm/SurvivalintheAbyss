#pragma once

#include "IShader.h"

class PixelShader : public IShader //순수 가상함수(우클릭->빠른작업->순수가상구현)
{
public:
	~PixelShader();

	// IShader을(를) 통해 상속됨
	virtual void Create(const wstring path, const string entryName) override;
	virtual void Clear() override;
	virtual void SetShader() override;

	ID3D11PixelShader* GetResource() { return shader; }
	ID3DBlob* GetBlob() { return blob; }

private:
	ID3D11PixelShader* shader = nullptr;
	ID3DBlob* blob = nullptr;

};