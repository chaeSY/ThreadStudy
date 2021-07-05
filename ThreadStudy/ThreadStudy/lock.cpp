#include "include.h"

std::vector<int> v;
std::mutex m;

void Push()
{
	// lock���� �����Ͱ� �߸����̴°� ������ ������, ���� ������ �̱۽����庸�� ������ ����

	for (int i = 0; i < 10000; ++i)
	{
		m.lock();

		v.push_back(i);

		m.unlock();
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