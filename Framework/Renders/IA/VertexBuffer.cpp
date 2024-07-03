#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	// SAFE_RELEASE�� ID3D�� �����ϴ� �������̽��� �����ϴ� ��ɾ��̴�.
	// ID3D�� �����ϴ� �����͵��� ���α׷��Ӱ� ����� ���� �ƴ� DirectX���� ����� �޶�� ��û�ϴ� �����͵��̴� ����
	// ���α׷��Ӱ� ���Ƿ� ����°��� �Ұ����� release�� �̿��� ������ �޶�� DirectX���� ��û�ؾ� �Ѵ�.
	// D3D�� DELETE, ID3D�� RELEASE (I�� ������ ������ RELEASAE)
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	// DC�� DeviceContext ���ڷ� DirectX���� �׸��� �׸��� ���� ������ ���������� ������ �����͸� �ְų� �����ϴ� ������ DeviceContext�� �����ϰ� ����Ѵ�.
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
