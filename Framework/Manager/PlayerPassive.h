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
	int playerPsvCount = 0;			// �÷��̾ ������ ���۰��� �нú� ����

	int hpIncreaseCount = 0;		// Hp���� count ��
	int attackIncreaseCount = 0;	// Atk���� count ��
	int defenceIncreaseCount = 0;	// Def���� count ��
	int speedIncreaseCount = 0;		// Spd���� count��

	int PsvHp = 0;					// �÷��� �Ǵ� Hp ��ġ
	int PsvAtk = 0;					// �÷��� �Ǵ� Atk ��ġ
	int PsvDef = 0;					// �÷��� �Ǵ� Def ��ġ
	float PsvSpd = 0.0f;			// �÷��� �Ǵ� Spd ��ġ

	// SetPsv������ ���� �ɷ�ġ ������ ����ǵ��� �ϱ�
};