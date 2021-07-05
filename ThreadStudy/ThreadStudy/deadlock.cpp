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
	// UserManager���� �ڽ��� mutex�� ȹ���ϰ�, AccountManager�� GetAccount�� ȣ���Ͽ�, mutex�� ȹ���Ϸ��� ��.
	// ���ÿ�, AccountManager�� �ڽ��� mutex�� ȹ���ϰ�, UserManager�� GetUser�� ȣ���Ͽ�, mutex�� ȹ���Ϸ� ��.
	// �ڽ��� mutex�� ��� �ִ� ���¿��� ������ mutex�� �������� ����ϰ� �ִ� ��Ȳ

	std::thread t1(Func1);
	std::thread t2(Func2);

	if(t1.joinable())
		t1.join();

	if (t2.joinable())
		t2.join();
}