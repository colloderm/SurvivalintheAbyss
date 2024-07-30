#pragma once

// Ÿ�� �ϳ��� ������ ���� �����͵��� ������ִ� Ŭ����
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

	// �׸��� �׷����� ���� ������ ��
	Color color = Values::Magenta;

	Vector2 startUV = Values::ZeroVec2;
	Vector2 endUV = Values::ZeroVec2;

	ID3D11ShaderResourceView* srv = nullptr;

	// �� Ÿ���� Ÿ�ϸ��� ���° Ÿ������ ������ִ� ��ȣ
	// -1 == ���������� ���� ��
	uint index = -1;
};