#include "UserManager.h"
#include "AccountManager.h"

User* UserManager::GetUser(int id)
{
	std::lock_guard<mutex> lockguard(_mutex);
	// user�� ã�Ƽ� return
	return nullptr;
}

void UserManager::ProcessSave()
{
	std::lock_guard<mutex> lockguard(_mutex);
	
	Account* account = AccountManager::Instance().GetAccount(100);;
}
