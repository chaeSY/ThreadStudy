#pragma once
#include "include.h"

class User
{

};

class UserManager
{
public:
	static UserManager& Instance()
	{
		static UserManager instance;
		return instance;
	}

	User* GetUser(int id);
	void ProcessSave();

private:
	std::mutex _mutex;
};