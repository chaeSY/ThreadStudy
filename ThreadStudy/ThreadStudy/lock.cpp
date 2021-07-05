#include "include.h"

std::vector<int> v;
std::mutex m;

void Push()
{
	// lock으로 데이터가 잘못쓰이는걸 방지는 했지만, 경합 때문에 싱글스레드보다 느리게 동작

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