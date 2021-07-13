#include "include.h"
#include <windows.h>

mutex m;
queue<int> q;
HANDLE eventHandle;

void Producer()
{
	while(true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		::SetEvent(eventHandle); 

		this_thread::sleep_for(10000000ms);
	}
}

void Consumer()
{
	while (true)
	{
		::WaitForSingleObject(eventHandle, INFINITE);

		unique_lock<mutex> lock(m);
		if (!q.empty())
		{
			int data = q.front();
			q.pop();

			cout << data << endl; 
		}
	}
}

int main()
{
	BOOL bManualReset = FALSE;
	BOOL bInitialState = FALSE;

	eventHandle = ::CreateEvent(NULL, bManualReset, bInitialState, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(eventHandle);
}