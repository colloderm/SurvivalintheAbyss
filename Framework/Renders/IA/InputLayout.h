#pragma once

/*
InputLayout
- 정점 데이터의 데이터 구조를 정의
- 정점 데이터의 각 요소(위치, 색상, 그림 좌표 등)의 형식, 크기, 순서 등을 지정
- IA단계에서 VS로 데이터를 전달하기 전에 정점 데이터를 받고 해당 데이터를 옳바르게 해석하기 위해 사용
- VertexType을 이용하여 정의
*/

class InputLayout
{
public:
	~InputLayout();

	// Blob은 DirectX에 요청해 만든 Buffer나 Shader등의 프로그램의 데이터를 가지고 있는 메모리 블록이다.
	// 우리는 해당 Buffer나 Shader에 직접적으로 접근할 수 없지만 해당 데이터를 가지고 있는 Blob에 접근해 내용물을 쓸 수 있다.
	void Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count, ID3DBlob* blob);

	void SetIA();

private:
	ID3D11InputLayout* il = nullptr;
};