#pragma once

class PlayerPassive
{
public:
	PlayerPassive();
	~PlayerPassive();

	void Update();

	void PsvSave(string path);
	void PsvLoad(string path);

	int GetPsvHp() { return PsvHp; }
	int GetPsvAtk() { return PsvAtk; }
	int GetPsvDef() { return PsvDef; }
	int GetPsvSpd() { return PsvSpd; }

private:
	int PsvHp = 0;
	int PsvAtk = 0;
	int PsvDef = 0;
	float PsvSpd = 0;

	// SetPsv데이터 만들어서 능력치 얻으면 적용되도록 하기
};