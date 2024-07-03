#pragma once

#include "TextureRect.h"

class ShadedBuffer :public ShaderBuffer
{
public:
	ShadedBuffer() 
		: ShaderBuffer(&data, sizeof(data))
	{
		data.selection = 1;

		data.blurCount = 1;
		data.textureSize = Vector2(0, 0);
	}

	// *(포인터)로 받는 이유는 다른 클래스에 있는 데이터를 
	// GUI가 바꾸기 위해서는 포인터로 받아주는게 수월하기 때문이다. 
	int* GetSelPtr() { return &data.selection; }
	int* GetBlurPtr() { return &data.blurCount; }

	void SetTextureSize(Vector2 size)
	{
		data.textureSize = size;
	}

	struct Data
	{
		int selection;			// 효과 지정 번호

		int blurCount;			// 블러의 세기
		Vector2 textureSize;	// 그림 사이즈
	};
private:
	Data data;
};

class AlphaBuffer : public ShaderBuffer
{
public:
	AlphaBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		data.alphaColor = 0xff555566;
		data.alphaCount = 0.0f;
		data.alpha = false;
	}

	float GetAlphaCount() { return data.alphaCount; }
	void SetAlphaCount(float ac) { data.alphaCount = ac; }
	float* GetACPtr() { return &data.alphaCount; }

	Color GetAlphaColor() { return data.alphaColor; }
	void SetAlphaColor(Color color) { data.alphaColor = color; }

	bool* GetAlphaPtr() { return &data.alpha; }

	// 16, 32, 64 같은 16의 2배수 만큼만 건내줄 수 있다.
	struct Data
	{
		Color alphaColor;	// 투명화 색상 // 16
		float alphaCount;	// 투명화 정도 // 4
		bool alpha;			// 투명화 여부 // 1
		// 여기까지의 데이터는 총 21 Byte 즉, 11바이트가 더 필요함
		bool dummys[11];	// bool값 11개를 만들어 부족한 데이터 패딩
	};
private:
	Data data;
};

class ShadedTexture : public TextureRect
{
public:
	ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	~ShadedTexture();

	void Update();
	void Render();
	void GUI();

private:
	ShadedBuffer* sb = nullptr;
	AlphaBuffer* ab = nullptr;
};