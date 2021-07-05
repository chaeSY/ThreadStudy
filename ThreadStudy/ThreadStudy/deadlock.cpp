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



// ���� �ذ��. 
// 1. Lock�� ������ �����Ѵ�.
// mutex�� id�� �ο��Ͽ� id�� ū �������� lock�Ѵٰų�.. �ϴ� ���

// std::lock(m1, m2, ...)
// ���ڷ� ���� mutex�� ���������� ������ �����ϸ� lock�� �ɾ���
// unlock�� ���� ���൵ ������ lock_guard�� adopt_lock �ɼ��� �־��ָ� lock_guard���� ���ؽ��� ȹ���� �� lock�� ���� �ʰ�, ���߿� �Ҹ��� �� unlock�� ���ش�.
// std::lock(m1, m2);
// lock_guard<mutex> g1(m1, std::adopt_lock);
// lock_guard<mutex> g2(m2, std::adopt_lock);
// adopt_lock: �̹� lock�� ���´ϱ� ���߿� �Ҹ�� �� Ǯ���ֱ⸸ �ϰŶ�.