#include "AccountManager.h"
#include "UserManager.h"

Account* AccountManager::GetAccount(int id)
{
	std::lock_guard<std::mutex> lockguard(_mutex);
	// account�� ã�Ƽ� return
	return nullptr;
}

void AccountManager::ProcessLogin()
{
	std::lock_guard<std::mutex> guard(_mutex);
	User* user = UserManager::Instance().GetUser(100);
}