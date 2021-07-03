#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> sum = 0;

void Add()
{
	for (int i = 0; i < 100'0000; ++i)
	{
		sum.fetch_add(1);
	}
}

void Sub()
{
	for (int i = 0; i < 100'0000; ++i)
	{
		sum.fetch_add(-1);
	}
}

void main()
{
	std::thread t(Add);
	std::thread t1(Sub);

	if (t.joinable())
		t.join();

	if (t1.joinable())
		t1.join();

	cout << sum << endl;
}