#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed)
	: clipName(clipName), frameCount(frameCount), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	// �̹����� �ʺ�� ���� �ҷ�����
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// �ִϸ��̼��� �׷��� �ִ� �κ��� ũ��
	Vector2 clipSize = endPos - startPos;

	// x�� frameCount�� ������ ������
	// x������ �ִϸ��̼��� �귯���� ��������Ʈ�� �̿��ϰ� �ֱ� ����
	Vector2 frameSize; // �׸� �ϳ��� ũ��
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// �ؼ��� �׸��� uv��ǥ�� ���ϱ⵵ �Ѵ�.
	// texelFrameSize�� uv��ǥ���� �ִϸ��̼� �ϳ��� ũ�⸦ ���Ѵ�.
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// texelStartPos�� uv��ǥ���� ���� ��ġ���� ���Ѵ�.
	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++)
	{
		// uv��ǥ���� �ִϸ��̼� �ϳ��� �׸� ��ġ�� ����ؼ�
		keyFrame.x = texelStartPos.x + (texelFrameSize.x * i);
		keyFrame.y = texelStartPos.y;

		// keyFrames�� �־�д�.
		keyFrames.push_back(keyFrame);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
	{
		SAFE_DELETE(clip.second);
	}
}

void Animator::Update()
{
	// �ִϸ��̼� ��� �ð��� playRate���� Ŀ���ٸ� ���� �׸����� �����Ѵ�.
	if (deltaTime >= playRate)
	{
		// ������� �ƴ϶��
		if (currentClip->bReversed == false)
		{
			// ������ �ε��� ����
			// ������ �ε��� == ���� �� �׸��� ��ȣ
			currentFrameIndex++;

			// �׸��� ��ȣ�� ������ ī��Ʈ�� ���ٸ� �迭�� ũ�⸦ ����°ű� ������ 0���� �ʱ�ȭ ���ش�.
			// �� �κ��� ������ ����� �κ��̴�.
			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0;

			// ���� ������ �������� ���� �������� �ִϸ��̼ǿ� 
			// ������ �ε��� ��ȣ�� �׸��� �����Ѵ�.
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else // ������� ���
		{
			// ������ �ε��� ����
			// ������̴ϱ� �ڿ������� 0���� �����ϱ� ����
			currentFrameIndex--;

			if (currentFrameIndex == -1)
				currentFrameIndex = currentClip->frameCount - 1; // �迭�� �ִ�ġ�� ����

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}
	else // ���� deltaTime�� playRate�� �Ѿ�� �ʾҴٸ�
		deltaTime += Time::Delta();
}

// �ִϸ����Ͱ� ����� �� �ִ� �ִϸ��̼� Ŭ���� �־��ִ� �Լ�
void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	// ���� �������� Ŭ���� �ְ�
	if (currentClip != nullptr)
		// Ŭ���� �̸��� �����Ű�� ���� �̸��� ���ٸ�
		if (currentClip->clipName == clipName)
			return; // �ٽ� ������.

	// Ŭ���� �����Ѵٸ�
	if (CheckExist(clipName))
	{
		// ������ Ŭ�� �Ѱ��ְ�
		currentClip = animClips.find(clipName)->second;
		// deltaTime �ʱ�ȭ
		deltaTime = 0.0f;

		// ������� Ŭ���̶��
		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}
