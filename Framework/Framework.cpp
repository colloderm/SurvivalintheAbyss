#include "Framework.h"

void CharacterManager::SetStat(int* stat)
{
	characterHp = stat[STAT::HP];
	characterAttack = stat[STAT::ATK];
	characterDefence = stat[STAT::DEF];
	characterSpeed = stat[STAT::SPD];
	Gold = stat[STAT::GOLD];
}

//�޸���?

/*
������ ����������
IA - InputAssembler : �Է�
------------ - (�ȼ����� �ݺ�)--------------
VS - VertextShader : �����׸���
RS - RasterizerState : ������ ���� ���̿� �ȼ� �׸���(�� ä��� - ���� ����)
PS - PixelShader : �ȼ��� �� �ֱ�
-------------------------------------- -
OM - OutMarge : ���
*/