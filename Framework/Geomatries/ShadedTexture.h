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

	// *(������)�� �޴� ������ �ٸ� Ŭ������ �ִ� �����͸� 
	// GUI�� �ٲٱ� ���ؼ��� �����ͷ� �޾��ִ°� �����ϱ� �����̴�. 
	int* GetSelPtr() { return &data.selection; }
	int* GetBlurPtr() { return &data.blurCount; }

	void SetTextureSize(Vector2 size)
	{
		data.textureSize = size;
	}

	struct Data
	{
		int selection;			// ȿ�� ���� ��ȣ

		int blurCount;			// ���� ����
		Vector2 textureSize;	// �׸� ������
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

	// 16, 32, 64 ���� 16�� 2��� ��ŭ�� �ǳ��� �� �ִ�.
	struct Data
	{
		Color alphaColor;	// ����ȭ ���� // 16
		float alphaCount;	// ����ȭ ���� // 4
		bool alpha;			// ����ȭ ���� // 1
		// ��������� �����ʹ� �� 21 Byte ��, 11����Ʈ�� �� �ʿ���
		bool dummys[11];	// bool�� 11���� ����� ������ ������ �е�
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