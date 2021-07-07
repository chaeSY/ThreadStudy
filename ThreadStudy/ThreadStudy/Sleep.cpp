#include "include.h"

class SleepLock
{
public:
	void lock()
	{
		bool expected = false;
		bool desired = true;
		while (!bLocked.compare_exchange_strong(expected, desired))
		{
			expected = false;

			//this_thread::sleep_for(std::chrono::milliseconds(100)); 
			this_thread::yield();
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
SleepLock sl;

void Add()
{
	for (int i = 0; i < 1000000; ++i)
	{
		std::lock_guard<SleepLock> guard(sl);
		++sum;
	}
}

void Sub()
{
	for (int i = 0; i < 1000000; ++i)
	{
		std::lock_guard<SleepLock> guard(sl);
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