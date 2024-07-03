#include "Framework.h"
#include "AnimationRect.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation)
	:TextureRect(position, size, rotation)
{
	animator = new Animator();

	// Ŭ�� ���� �� ����
	{
		// ����� �׸� �ҷ�����
		Texture2D* srcTex = new Texture2D(TexturePath + L"Goblin/GoblinWalk.png");

		// �ִϸ��̼� Ŭ�� ����
		AnimationClip* WalkDR = new AnimationClip(L"WalkDR", srcTex, 4, { 0,						   0 }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
		AnimationClip* WalkDL = new AnimationClip(L"WalkDL", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f  });
		AnimationClip* WalkUR = new AnimationClip(L"WalkUR", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f  }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f });
		AnimationClip* WalkUL = new AnimationClip(L"WalkUL", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight()		  });

		// �ִϸ��̼� Ŭ�� �߰�
		animator->AddAnimClip(WalkDR);
		animator->AddAnimClip(WalkDL);
		animator->AddAnimClip(WalkUR);
		animator->AddAnimClip(WalkUL);

		SAFE_DELETE(srcTex);

	}

	// �⺻ �ִϸ��̼� ����
	// �̰� ���ٸ� �׸� �׸��� ��� ����
	animator->SetCurrentAnimClip(L"WalkDR");

	// States ����
	{
		// Sampler
		D3D11_SAMPLER_DESC sDesc;
		States::GetSamplerDesc(&sDesc);
		sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&sDesc, &sampler);

		// Blend
		D3D11_BLEND_DESC bDesc;
		States::GetBlendDesc(&bDesc);
		bDesc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&bDesc, &blend);
	}
}

AnimationRect::~AnimationRect()
{
	SAFE_DELETE(animator);
}

void AnimationRect::Update()
{
	/*if (Keyboard::Get()->Down('W'))
	{
		stUD = StateUD::UP;
	}
	else if (Keyboard::Get()->Down('S'))
	{
		stUD = StateUD::DOWN;
	}

	if (Keyboard::Get()->Down('A'))
	{
		stLR = StateLR::LEFT;
	}
	else if (Keyboard::Get()->Down('D'))
	{
		stLR = StateLR::RIGHT;
	}

	switch (stUD)
	{
	case StateUD::UP:
	{
		switch (stLR)
		{
		case StateLR::LEFT:
		{
			animator->SetCurrentAnimClip(L"WalkUL");
		}break;
		case StateLR::RIGHT:
		{
			animator->SetCurrentAnimClip(L"WalkUR");
		}break;
		}
	}break;
	case StateUD::DOWN:
	{
		switch (stLR)
		{
		case StateLR::LEFT:
		{
			animator->SetCurrentAnimClip(L"WalkDL");
		}break;
		case StateLR::RIGHT:
		{
			animator->SetCurrentAnimClip(L"WalkDR");
		}break;
		}
	}break;
	}*/

	animator->Update();

	SetAnimUV();

	__super::Update();
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &sampler);
	DC->OMSetBlendState(blend, nullptr, (UINT)0xFFFFFFFF);

	__super::Render();
}

// vertices�� ���� �ִ� uv���� �ִϸ��̼� ��ġ�� uv������ ����
void AnimationRect::SetAnimUV()
{
	D3D11_MAPPED_SUBRESOURCE subRe;

	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
	{
		// 0�� == ���ϴ� == 0, 1
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		// 1�� == ���� == 1, 0
		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		// 2�� == ���ϴ� == 1, 1
		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		// 3�� == �»�� == 0, 0
		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;

		memcpy(subRe.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	}
	DC->Unmap(vb->GetResource(), 0);
}
