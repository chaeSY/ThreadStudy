#pragma once
#include "include.h"

class Account
{

};

class AccountManager
{
public:
	static AccountManager& Instance()
	{
		static AccountManager instance;
		return instance;
	}

	Account* GetAccount(int id);
	void ProcessLogin();

private:
	std::mutex _mutex;
};