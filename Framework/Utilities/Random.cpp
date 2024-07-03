#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int min, int max)
{
	/*
	random_device는 프로그래머가 제어 할 수 없는 난수값을 만들어내는 클래스이며,
	지역에서 벗어났을때 자동으로 소멸된다.

	또한, 호출할 때 마다 자동으로 랜덤한 난수값을 만들어낸다.
	*/
	random_device randD; // 럭키 srand라고 함?(강사피셜)

	/*
	uniform_int_distribution은 정수형의 랜덤값의 범위를 만들어내는 클래스

	일반적인 uniform_int 보다 더 정교하게 작동하며, 
	<>에 원하는 자료형을 집어넣어 해당 자료형의 반환값을 만들어 낼 수 있다.

	또한, rand를 이용한 랜덤값과 달리 최소값과 최대값의 지정이 자유롭다.
	이때 반환되는 랜덤값은 최소값과 최대값이 포함된 값이 출력된다.
	Ex) intRand(100, 200) == 100~200 까지 표현
	*/
	uniform_int_distribution<int> intRand(min, max);

	/*
	랜덤값을 출력하기 위해서는 위에서 만든 유니폼에 괄호를 열어 
	괄호에 랜덤 디바이스를 넣어주면 자동으로 랜덤값이 반환된다.

	이때 똑같은 코드를 여러번 실행해도 매번 랜덤 디바이스의 난수값이 달라진다.
	*/
	int temp = intRand(randD);

	return temp;
}

float Random::GetRnadomFloat(float min, float max)
{
	random_device randD;

	/*
	uniform_real_distribution은 실수형의 랜덤값의 범위를 만들어내는 클래스

	이때 주의할 사항으로 float의 랜덤범위는 일반적인 생각보다 훨씬 크기에 사용에 주의해야 한다.
	Ex) floatRand(0.1, 0.5) == 0.1000000~0.5000000
	Ex) == 0.12541267 같은게 나올수도 있다.
	*/
	uniform_real_distribution<float> floatRand(min, max);

	float temp = floatRand(randD);

	return temp;
}
