#include "include.h"

vector<int> v;

// stl �ڷᱸ���� ��Ƽ�����忡�� �������� �ʴ´ٰ� �����ؾ� ��.
// vector�� capacity�� �÷��� �� �޸𸮸� �����ϱ� ������ double free ������ ũ���ð� �� �� ����

void Push()
{
	for (int i = 0; i < 10000; ++i)
	{
		v.push_back(i);
	}
}

void main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}