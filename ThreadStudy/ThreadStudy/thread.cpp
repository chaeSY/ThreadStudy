#include "include.h"

// C++11에서 thread가 표준으로 들어옴
//::CreateThread 와 같은 Window api의 thread를 사용한다면, 혹여나 나중에 리눅스로 서버를 옮겨야 하는 상황이 생길 때 문제가 됨.

using namespace std;

void EntryPoint()
{
	cout << "Hello Thread" << endl;
}

void EntryPoint_OneParam(int num)
{
	cout << "Hello Thread One Param: " << num << endl;
}

int main()
{
	cout << "Hello Main" << endl;

	// parameter가 없는 entry point
	std::thread t(EntryPoint);

	// parameter가 들어간 entry point
	// variadic template으로 구현됨.
	std::thread t2(EntryPoint_OneParam, 2);

	// 여러개의 thread
	vector<std::thread> v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(std::thread(EntryPoint_OneParam, i));
	}

	if (t.joinable())
	{
		t.join();
	}

	if (t2.joinable())
	{
		t2.join();
	}

	for (int i = 0; i < 10; ++i)
	{
		if (v[i].joinable())
		{
			v[i].join();
		}
	}
}
