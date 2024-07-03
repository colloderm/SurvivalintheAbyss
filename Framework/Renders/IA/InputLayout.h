#pragma once

/*
InputLayout
- ���� �������� ������ ������ ����
- ���� �������� �� ���(��ġ, ����, �׸� ��ǥ ��)�� ����, ũ��, ���� ���� ����
- IA�ܰ迡�� VS�� �����͸� �����ϱ� ���� ���� �����͸� �ް� �ش� �����͸� �ǹٸ��� �ؼ��ϱ� ���� ���
- VertexType�� �̿��Ͽ� ����
*/

class InputLayout
{
public:
	~InputLayout();

	// Blob�� DirectX�� ��û�� ���� Buffer�� Shader���� ���α׷��� �����͸� ������ �ִ� �޸� ����̴�.
	// �츮�� �ش� Buffer�� Shader�� ���������� ������ �� ������ �ش� �����͸� ������ �ִ� Blob�� ������ ���빰�� �� �� �ִ�.
	void Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count, ID3DBlob* blob);

	void SetIA();

private:
	ID3D11InputLayout* il = nullptr;
};