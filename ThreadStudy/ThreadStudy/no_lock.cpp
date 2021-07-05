#include "include.h"

vector<int> v;

// stl 자료구조는 멀티스레드에서 동작하지 않는다고 가정해야 함.
// vector는 capacity를 늘려줄 때 메모리를 삭제하기 때문에 double free 문제로 크래시가 날 수 있음

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