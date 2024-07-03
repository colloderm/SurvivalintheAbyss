#pragma once

// IShader�� CPU���� GPU���� ���̴� ����� ������ ����
// ShaderBuffer�� �ǳ��� �����͸� IShader�� ����� ������ �����Ѵ�.
// � ���̴� ���Ͽ��� � �̸��� �Լ��� �����϶�. <- �̰Ÿ� �ַ���
class IShader
{
public:
	// vortual�� ������ �����Լ��� ������ ��� =0�� ���� ���
	// �ش� �Լ��� ���� �� �� ���� ���� ���� �Լ��� �ȴ�.
	// �̷��� ���� ���� �Լ��� ���� Ŭ������ �Լ��� �����ΰ� �������� �ʱ� ������
	// �ش� Ŭ������ ���������� �����ϴ� ���� �Ұ���������, 
	// �ݵ�� �ش� Ŭ������ ��ӹ��� �ڽ� Ŭ������ ������ ����� ���������.
	// �ڽ�Ŭ�������� ���� �ش� �Լ����� �������� ������ �ڽ� Ŭ������ ������ �Ұ���������. (�߿�)

	// ����
	virtual void Create(const wstring path, const string entryName) = 0;
	// �Ҹ�
	virtual void Clear() = 0;
	// ����
	virtual void SetShader() = 0;

protected:
	// ���ο��� �����͸� �䱸�ϴ� ������ �ֱ⿡ ���������͸� ���
	void CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob);

	wstring path = L"";		// ���̴� ���� ���
	string entryName = "";	// ������ �̸�(���̴� ���Ͽ��� ���� �� �Լ� �̸�)

private:
	void CheckShaderError(HRESULT hr, ID3DBlob* error);
};