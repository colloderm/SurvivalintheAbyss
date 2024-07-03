#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed)
	: clipName(clipName), frameCount(frameCount), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	// 이미지의 너비와 높이 불러오기
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// 애니메이션이 그려져 있는 부분의 크기
	Vector2 clipSize = endPos - startPos;

	// x를 frameCount로 나누는 이유는
	// x축으로 애니메이션이 흘러가는 스프라이트를 이용하고 있기 때문
	Vector2 frameSize; // 그림 하나의 크기
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// 텍셀은 그림의 uv좌표를 뜻하기도 한다.
	// texelFrameSize는 uv좌표상의 애니메이션 하나의 크기를 뜻한다.
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// texelStartPos는 uv좌표상의 시작 위치점을 뜻한다.
	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++)
	{
		// uv좌표상의 애니메이션 하나를 그릴 위치를 계산해서
		keyFrame.x = texelStartPos.x + (texelFrameSize.x * i);
		keyFrame.y = texelStartPos.y;

		// keyFrames에 넣어둔다.
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
	// 애니메이션 경과 시간이 playRate보다 커졌다면 다음 그림으로 변경한다.
	if (deltaTime >= playRate)
	{
		// 역재생이 아니라면
		if (currentClip->bReversed == false)
		{
			// 프레임 인덱스 증가
			// 프레임 인덱스 == 실행 할 그림의 번호
			currentFrameIndex++;

			// 그림의 번호가 프레임 카운트와 같다면 배열의 크기를 벗어나는거기 때문에 0으로 초기화 해준다.
			// 이 부분이 루프를 만드는 부분이다.
			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0;

			// 지금 실행할 프레임은 지금 실행중인 애니메이션에 
			// 프레임 인덱스 번호의 그림을 실행한다.
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else // 역재생일 경우
		{
			// 프레임 인덱스 감소
			// 역재생이니까 뒤에서부터 0으로 실행하기 때문
			currentFrameIndex--;

			if (currentFrameIndex == -1)
				currentFrameIndex = currentClip->frameCount - 1; // 배열의 최대치로 설정

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}
	else // 아직 deltaTime이 playRate를 넘어서지 않았다면
		deltaTime += Time::Delta();
}

// 애니메이터가 사용할 수 있는 애니메이션 클립을 넣어주는 함수
void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	// 현재 실행중인 클립이 있고
	if (currentClip != nullptr)
		// 클립의 이름이 실행시키고 싶은 이름과 같다면
		if (currentClip->clipName == clipName)
			return; // 다시 나간다.

	// 클립이 존재한다면
	if (CheckExist(clipName))
	{
		// 실행할 클립 넘겨주고
		currentClip = animClips.find(clipName)->second;
		// deltaTime 초기화
		deltaTime = 0.0f;

		// 역재생할 클립이라면
		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}
