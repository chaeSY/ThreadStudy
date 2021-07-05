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