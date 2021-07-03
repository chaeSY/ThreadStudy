#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

int sum = 0; // 공유메모리

void Add()
{
	for (int i = 0; i < 100'0000; ++i)
	{
		++sum;

		/* register pseudo code
		int eax = sum;
		eax = eax + 1;
		sum = eax;
		*/
	}
}

void Sub()
{
	for (int i = 0; i < 100'0000; ++i)
	{
		--sum;

		/* register pseudo code
		int eax = sum;
		eax = eax - 1;
		sum = eax;
		*/
	}
}

void main()
{
	std::thread t(Add);
	std::thread t1(Sub);

	if(t.joinable())
		t.join();

	if (t1.joinable())
		t1.join();

	cout << sum << endl;
}