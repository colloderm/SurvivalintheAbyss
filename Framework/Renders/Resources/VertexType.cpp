#include "Framework.h"
#include "VertexType.h"

/*
D3D11_INPUT_ELEMENT_DESC

SemanticName			: 정점 데이터의 의미를 나타내는 문구
SemanticIndex			: 이름이 중복될경우 구분하기 위한 숫자
Format					: 데이터의 해석 방식을 나타냄
InputSlot				: 입력 슬롯의 번호
AligendByteOffset		: 정점 데이터의 바이트 단위 오프셋(간격 & 크기)
InputSlotClass			: 사용되는 데이터의 형식을 지정
InstanceDataStepRate	: 인스턴스 마다 데이터를 읽을 때 대기할 시간
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
	//POSITION이라고 부르고, 중복일 때 0번에 위치, 플롯형태의 R32G32B32 데이터, 0번에 집어넣고, 처음부터, 정점데이터로 읽고, 대기시간은 0
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