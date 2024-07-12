#include "Framework.h"

void CharacterManager::SetStat(int* stat)
{
	characterHp = stat[STAT::HP];
	characterAttack = stat[STAT::ATK];
	characterDefence = stat[STAT::DEF];
	characterSpeed = stat[STAT::SPD];
	Gold = stat[STAT::GOLD];
}

//메모장?

/*
렌더링 파이프라인
IA - InputAssembler : 입력
------------ - (픽셀마다 반복)--------------
VS - VertextShader : 정점그리기
RS - RasterizerState : 정점과 정점 사이에 픽셀 그리기(점 채우기 - 색은 없음)
PS - PixelShader : 픽셀에 색 넣기
-------------------------------------- -
OM - OutMarge : 출력
*/