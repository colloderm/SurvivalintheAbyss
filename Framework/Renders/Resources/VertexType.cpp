#include "Framework.h"
#include "VertexType.h"

/*
D3D11_INPUT_ELEMENT_DESC

SemanticName			: ���� �������� �ǹ̸� ��Ÿ���� ����
SemanticIndex			: �̸��� �ߺ��ɰ�� �����ϱ� ���� ����
Format					: �������� �ؼ� ����� ��Ÿ��
InputSlot				: �Է� ������ ��ȣ
AligendByteOffset		: ���� �������� ����Ʈ ���� ������(���� & ũ��)
InputSlotClass			: ���Ǵ� �������� ������ ����
InstanceDataStepRate	: �ν��Ͻ� ���� �����͸� ���� �� ����� �ð�
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
	//POSITION�̶�� �θ���, �ߺ��� �� 0���� ��ġ, �÷������� R32G32B32 ������, 0���� ����ְ�, ó������, ���������ͷ� �а�, ���ð��� 0
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[]
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

D3D11_INPUT_ELEMENT_DESC VertexTile::descs[]
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"INDEX", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};