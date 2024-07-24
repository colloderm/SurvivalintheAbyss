#pragma once

class PlayerPassive
{
public:
	PlayerPassive();
	~PlayerPassive();

	void Update();

	void PsvSave(string path);
	void PsvLoad(string path);

	int SetIncHpCount(int incHpCount) { return hpIncreaseCount += incHpCount; }
	int SetIncAtkCount(int incAtkCount) { return attackIncreaseCount += incAtkCount; }
	int SetIncDefCount(int incDefCount) { return defenceIncreaseCount += incDefCount; }
	int SetIncSpdCount(float incSpdCount) { return speedIncreaseCount += incSpdCount; }

	int SetIncHp(int incHp) { return PsvHp += incHp; }
	int SetIncAtk(int incAtk) { return PsvAtk += incAtk; }
	int SetIncDef(int incDef) { return PsvDef += incDef; }
	float SetIncSpd(float incSpd) { return PsvSpd += incSpd; }

	int GetIncHpCount() { return hpIncreaseCount; }
	int GetIncAtkCount() { return attackIncreaseCount; }
	int GetIncDefCount() { return defenceIncreaseCount; }
	int GetIncSpdCount() { return speedIncreaseCount; }

	int GetPsvHp() { return PsvHp; }
	int GetPsvAtk() { return PsvAtk; }
	int GetPsvDef() { return PsvDef; }
	float GetPsvSpd() { return PsvSpd; }

private:
	int hpIncreaseCount = 0;
	int attackIncreaseCount = 0;
	int defenceIncreaseCount = 0;
	int speedIncreaseCount = 0;

	int PsvHp = 0;
	int PsvAtk = 0;
	int PsvDef = 0;
	float PsvSpd = 0.0f;

	// SetPsv데이터 만들어서 능력치 얻으면 적용되도록 하기
};