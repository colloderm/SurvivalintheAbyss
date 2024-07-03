#include "Framework.h"
#include "ShadedTexture.h"

ShadedTexture::ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	: TextureRect(position, size, rotation, path)
{
	sb = new ShadedBuffer();
	sb->SetTextureSize(Vector2(size.x, size.y));

	ab = new AlphaBuffer();

	SetShader(ShaderPath + L"TextureShader.hlsl");
}

ShadedTexture::~ShadedTexture()
{
	SAFE_DELETE(ab);
	SAFE_DELETE(sb);
}

void ShadedTexture::Update()
{
	if (Keyboard::Get()->Press(VK_LEFT))
	{
		ab->SetAlphaCount(ab->GetAlphaCount() - 0.01f);
	}
	else if (Keyboard::Get()->Press(VK_RIGHT))
	{
		ab->SetAlphaCount(ab->GetAlphaCount() + 0.01f);
	}

	// __super는 부모객체를 자동으로 호출하는 명령어이다.
	// 단점: 매크로가 힘들다
	__super::Update(); // == TextureRect::Update();

}

void ShadedTexture::Render()
{
	sb->SetPSBuffer(0);
	ab->SetPSBuffer(1);
	__super::Render();
}

void ShadedTexture::GUI()
{
	ImGui::Begin("Shader");
	{
		// RadioButton은 해당 UI공간에 하나만 선택될 수 있는 버튼이다.
		// RadioButton을 10개 만든다 하더라도 그 중에 하나만 고를 수 있다.
		ImGui::RadioButton("Normal",	sb->GetSelPtr(), 1);	// 기본값
		ImGui::RadioButton("Gray",		sb->GetSelPtr(), 2);	// 흑백처리
		ImGui::RadioButton("Negative",	sb->GetSelPtr(), 3);	// 색 반전
		ImGui::RadioButton("Blur",		sb->GetSelPtr(), 4);	// 블러처리
		ImGui::RadioButton("PivotRL",	sb->GetSelPtr(), 5);	// 좌우반전
		ImGui::RadioButton("PivotUD",	sb->GetSelPtr(), 6);	// 상하반전
		ImGui::RadioButton("OutLine",	sb->GetSelPtr(), 7);	// 외각선

		// 블러 세기 조절
		ImGui::SliderInt("BlurCount", sb->GetBlurPtr(), 1, 60);

		// 체크박스
		ImGui::Checkbox("Alpha", ab->GetAlphaPtr());
		ImGui::SliderFloat("AlphaCount", ab->GetACPtr(), 0, 1);

		Color color = ab->GetAlphaColor();
		if (ImGui::ColorPicker3("AlphaColor", color))
		{
			ab->SetAlphaColor(color);
		}
	}
	ImGui::End();
}
