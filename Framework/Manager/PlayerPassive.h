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

	int PsvCount() { return playerPsvCount; }

private:
	int playerPsvCount = 0;			// 플레이어가 소유한 업글가능 패시브 개수

	int hpIncreaseCount = 0;		// Hp업한 count 수
	int attackIncreaseCount = 0;	// Atk업한 count 수
	int defenceIncreaseCount = 0;	// Def업한 count 수
	int speedIncreaseCount = 0;		// Spd업한 count수

	int PsvHp = 0;					// 플러스 되는 Hp 수치
	int PsvAtk = 0;					// 플러스 되는 Atk 수치
	int PsvDef = 0;					// 플러스 되는 Def 수치
	float PsvSpd = 0.0f;			// 플러스 되는 Spd 수치

	// SetPsv데이터 만들어서 능력치 얻으면 적용되도록 하기
};