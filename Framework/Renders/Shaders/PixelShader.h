#pragma once

#include "IShader.h"

class PixelShader : public IShader //���� �����Լ�(��Ŭ��->�����۾�->����������)
{
public:
	~PixelShader();

	// IShader��(��) ���� ��ӵ�
	virtual void Create(const wstring path, const string entryName) override;
	virtual void Clear() override;
	virtual void SetShader() override;

	ID3D11PixelShader* GetResource() { return shader; }
	ID3DBlob* GetBlob() { return blob; }

private:
	ID3D11PixelShader* shader = nullptr;
	ID3DBlob* blob = nullptr;

};