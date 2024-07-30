#pragma once

// 타일 하나가 가지고 있을 데이터들을 명시해주는 클래스
class Tile
{
public:
	Vector3 GetPosition() { return position; }
	void SetPosition(Vector3 position) { this->position = position; }

	Vector2 GetStartUV() { return startUV; }
	void SetStartUV(Vector2 uv) { startUV = uv; }

	Vector2 GetEndUV() { return endUV; }
	void SetEndUV(Vector2 uv) { endUV = uv; }

	Color GetColor() { return color; }
	void SetColor(Color color) { this->color = color; }

	UINT GetIndex() { return index; }
	void SetIndex(UINT index) { this->index = index; }

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

private:
	Vector3 position = Values::ZeroVec3;

	// 그림이 그려지지 않은 공간의 색
	Color color = Values::Magenta;

	Vector2 startUV = Values::ZeroVec2;
	Vector2 endUV = Values::ZeroVec2;

	ID3D11ShaderResourceView* srv = nullptr;

	// 이 타일이 타일맵의 몇번째 타일인지 명시해주는 번호
	// -1 == 정상적이지 않은 값
	uint index = -1;
};