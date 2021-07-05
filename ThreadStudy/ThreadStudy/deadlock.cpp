#include "include.h"
#include "AccountManager.h"
#include "UserManager.h"

void Func1()
{
	for (int i = 0; i < 1000; ++i)
	{
		UserManager::Instance().ProcessSave();
	}
}

void Func2()
{
	for (int i = 0; i < 1000; ++i)
	{
		AccountManager::Instance().ProcessLogin();
	}
}

void main()
{
	// UserManager에서 자신의 mutex를 획득하고, AccountManager의 GetAccount를 호출하여, mutex를 획득하려고 함.
	// 동시에, AccountManager는 자신의 mutex를 획득하고, UserManager의 GetUser를 호출하여, mutex를 획득하려 함.
	// 자신의 mutex를 들고 있는 상태에서 서로의 mutex를 얻으려고 대기하고 있는 상황

	std::thread t1(Func1);
	std::thread t2(Func2);

	if(t1.joinable())
		t1.join();

	if (t2.joinable())
		t2.join();
}



// 간단 해결법. 
// 1. Lock의 순서를 통일한다.
// mutex에 id를 부여하여 id가 큰 순서부터 lock한다거나.. 하는 방법

// std::lock(m1, m2, ...)
// 인자로 받은 mutex를 내부적으로 순서를 유지하며 lock을 걸어줌
// unlock은 직접 해줘도 되지만 lock_guard에 adopt_lock 옵션을 넣어주면 lock_guard에서 뮤텍스를 획득할 때 lock을 걸지 않고, 나중에 소멸할 때 unlock을 해준다.
// std::lock(m1, m2);
// lock_guard<mutex> g1(m1, std::adopt_lock);
// lock_guard<mutex> g2(m2, std::adopt_lock);
// adopt_lock: 이미 lock된 상태니까 나중에 소멸될 때 풀어주기만 하거라.