#pragma once

// 실질적인 애니메이션 이미지를 만들어 주는곳
class AnimationClip
{
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed = false);

private:
	wstring clipName = L"";
	vector<Vector2> keyFrames; // 클립 이미지 한 장의 시작점들을 저장해두는 변수
	UINT frameCount;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Vector2(0, 0);
	bool bReversed = false;
};

// 애니메이션 클립 실행 도구
class Animator
{
public:
	Animator();
	~Animator();

	void Update();

	// 현재 실행중인 이미지의 uv좌표값
	Vector2 GetCurrentFrame() { return currentFrame; }
	// 현재 실행중인 애니메이션의 텍셀프레임크기 // 실질적 그림의 하나 크기
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	// 현재 실행중인 이미지 srv 반환
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }
	
	// animClips에 애니메이션 클립 추가
	void AddAnimClip(AnimationClip* animClip);
	// 지금 실행시킬 클립 지정
	void SetCurrentAnimClip(wstring clipName);

	// 현재 실행중인 애니메이션 클립 이름 반환
	wstring GetCurrentClipName() { return currentClip->clipName; }

	// 이미지 전환 속도 변경
	void SetPlayRate(float playRate) { this->playRate = playRate; }

private:
	unordered_map<wstring, AnimationClip*> animClips;
	bool CheckExist(wstring clipName) { return animClips.find(clipName) != animClips.end(); }

	// 현재 실행중인 클립
	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0; // 현재 실행중인 클립의 실행번호
	Vector2 currentFrame = Vector2(0, 0);

	float deltaTime = 0.0f;
	
	// 이미지 전환 속도(기본) // 값이 크면 느리고 작으면 빠름
	float playRate = 1.0f / 15.0f;
};