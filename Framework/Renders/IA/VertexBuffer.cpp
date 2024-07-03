#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	// SAFE_RELEASE는 ID3D로 시작하는 인터페이스를 해제하는 명령어이다.
	// ID3D로 시작하는 데이터들은 프로그래머가 만드는 것이 아닌 DirectX한테 만들어 달라고 요청하는 데이터들이다 보니
	// 프로그래머가 임의로 지우는것이 불가능해 release를 이용해 해제해 달라고 DirectX에게 요청해야 한다.
	// D3D는 DELETE, ID3D는 RELEASE (I가 붙으면 무조건 RELEASAE)
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	// DC는 DeviceContext 약자로 DirectX에서 그림을 그리기 위한 렌더링 파이프라인 과정에 데이터를 넣거나 관리하는 모든것을 DeviceContext가 관리하고 담당한다.
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
