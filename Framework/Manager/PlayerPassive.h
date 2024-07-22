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

	// SetPsv������ ���� �ɷ�ġ ������ ����ǵ��� �ϱ�
};