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

	// __super�� �θ�ü�� �ڵ����� ȣ���ϴ� ��ɾ��̴�.
	// ����: ��ũ�ΰ� �����
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
		// RadioButton�� �ش� UI������ �ϳ��� ���õ� �� �ִ� ��ư�̴�.
		// RadioButton�� 10�� ����� �ϴ��� �� �߿� �ϳ��� �� �� �ִ�.
		ImGui::RadioButton("Normal",	sb->GetSelPtr(), 1);	// �⺻��
		ImGui::RadioButton("Gray",		sb->GetSelPtr(), 2);	// ���ó��
		ImGui::RadioButton("Negative",	sb->GetSelPtr(), 3);	// �� ����
		ImGui::RadioButton("Blur",		sb->GetSelPtr(), 4);	// ��ó��
		ImGui::RadioButton("PivotRL",	sb->GetSelPtr(), 5);	// �¿����
		ImGui::RadioButton("PivotUD",	sb->GetSelPtr(), 6);	// ���Ϲ���
		ImGui::RadioButton("OutLine",	sb->GetSelPtr(), 7);	// �ܰ���

		// �� ���� ����
		ImGui::SliderInt("BlurCount", sb->GetBlurPtr(), 1, 60);

		// üũ�ڽ�
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
