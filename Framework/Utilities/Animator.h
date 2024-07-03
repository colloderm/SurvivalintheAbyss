#pragma once

// �������� �ִϸ��̼� �̹����� ����� �ִ°�
class AnimationClip
{
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed = false);

private:
	wstring clipName = L"";
	vector<Vector2> keyFrames; // Ŭ�� �̹��� �� ���� ���������� �����صδ� ����
	UINT frameCount;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Vector2(0, 0);
	bool bReversed = false;
};

// �ִϸ��̼� Ŭ�� ���� ����
class Animator
{
public:
	Animator();
	~Animator();

	void Update();

	// ���� �������� �̹����� uv��ǥ��
	Vector2 GetCurrentFrame() { return currentFrame; }
	// ���� �������� �ִϸ��̼��� �ؼ�������ũ�� // ������ �׸��� �ϳ� ũ��
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	// ���� �������� �̹��� srv ��ȯ
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }
	
	// animClips�� �ִϸ��̼� Ŭ�� �߰�
	void AddAnimClip(AnimationClip* animClip);
	// ���� �����ų Ŭ�� ����
	void SetCurrentAnimClip(wstring clipName);

	// ���� �������� �ִϸ��̼� Ŭ�� �̸� ��ȯ
	wstring GetCurrentClipName() { return currentClip->clipName; }

	// �̹��� ��ȯ �ӵ� ����
	void SetPlayRate(float playRate) { this->playRate = playRate; }

private:
	unordered_map<wstring, AnimationClip*> animClips;
	bool CheckExist(wstring clipName) { return animClips.find(clipName) != animClips.end(); }

	// ���� �������� Ŭ��
	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0; // ���� �������� Ŭ���� �����ȣ
	Vector2 currentFrame = Vector2(0, 0);

	float deltaTime = 0.0f;
	
	// �̹��� ��ȯ �ӵ�(�⺻) // ���� ũ�� ������ ������ ����
	float playRate = 1.0f / 15.0f;
};