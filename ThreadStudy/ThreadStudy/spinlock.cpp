#include "include.h"

class SpinLock
{
public:
	void lock()
	{
		bool expected = false;
		bool desired = true;
		
		while (!bLocked.compare_exchange_strong(expected, desired))
		{
			expected = false; // expected가 내부에서 바뀌므로 false로 다시 셋팅
		}
	}

	void unlock()
	{
		bLocked.store(false);
	}

private:
	atomic<bool> bLocked = false;
};

int sum = 0;
std::mutex m;
SpinLock sl;

void Add()
{
	for (int i = 0; i < 1000000; ++i)
	{
		std::lock_guard<SpinLock> guard(sl);
		++sum;
	}
}

void Sub()
{
	for (int i = 0; i < 1000000; ++i)
	{
		std::lock_guard<SpinLock> guard(sl);
		--sum;
	}
}

void main()
{
	std::thread t(Add);
	std::thread t2(Sub);


	t.join();
	t2.join();

	cout << sum << endl;
}