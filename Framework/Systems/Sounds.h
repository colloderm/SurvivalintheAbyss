#pragma once

using namespace FMOD;

class Sounds : public SingletonBase<Sounds>
{
public:
	friend SingletonBase<Sounds>;

	void Update();
	
	void AddSound(string name, wstring file, bool loop = false);

	void Play(string name, float volum = 1.0f); // �ּ�0 ~ �ִ�1
	void Stop(string name);
	void Pause(string name);
	void Resum(string name);

	bool IsplayIng(string name);
	bool IsPause(string name);

	void SetVolum(string name, float volum);
	float GetVolum(string name);

private:
	Sounds();
	~Sounds();

private:
	System* system;
	Sound** sound;
	Channel** channel;

	UINT count;

	// ���� Ž���� �� ���� ���ִ� Ž����?
	map<string, Sound**> sounds;
	map<string, Sound**>::iterator iter;

	float volum;
};