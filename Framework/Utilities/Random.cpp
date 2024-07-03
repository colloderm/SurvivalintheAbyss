#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int min, int max)
{
	/*
	random_device�� ���α׷��Ӱ� ���� �� �� ���� �������� ������ Ŭ�����̸�,
	�������� ������� �ڵ����� �Ҹ�ȴ�.

	����, ȣ���� �� ���� �ڵ����� ������ �������� ������.
	*/
	random_device randD; // ��Ű srand��� ��?(�����Ǽ�)

	/*
	uniform_int_distribution�� �������� �������� ������ ������ Ŭ����

	�Ϲ����� uniform_int ���� �� �����ϰ� �۵��ϸ�, 
	<>�� ���ϴ� �ڷ����� ����־� �ش� �ڷ����� ��ȯ���� ����� �� �� �ִ�.

	����, rand�� �̿��� �������� �޸� �ּҰ��� �ִ밪�� ������ �����Ӵ�.
	�̶� ��ȯ�Ǵ� �������� �ּҰ��� �ִ밪�� ���Ե� ���� ��µȴ�.
	Ex) intRand(100, 200) == 100~200 ���� ǥ��
	*/
	uniform_int_distribution<int> intRand(min, max);

	/*
	�������� ����ϱ� ���ؼ��� ������ ���� �������� ��ȣ�� ���� 
	��ȣ�� ���� ����̽��� �־��ָ� �ڵ����� �������� ��ȯ�ȴ�.

	�̶� �Ȱ��� �ڵ带 ������ �����ص� �Ź� ���� ����̽��� �������� �޶�����.
	*/
	int temp = intRand(randD);

	return temp;
}

float Random::GetRnadomFloat(float min, float max)
{
	random_device randD;

	/*
	uniform_real_distribution�� �Ǽ����� �������� ������ ������ Ŭ����

	�̶� ������ �������� float�� ���������� �Ϲ����� �������� �ξ� ũ�⿡ ��뿡 �����ؾ� �Ѵ�.
	Ex) floatRand(0.1, 0.5) == 0.1000000~0.5000000
	Ex) == 0.12541267 ������ ���ü��� �ִ�.
	*/
	uniform_real_distribution<float> floatRand(min, max);

	float temp = floatRand(randD);

	return temp;
}
