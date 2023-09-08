#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include "MyException.h"

class User
{
private:
	string type;
	string username;
	string password;
	bool santaAccess;
	bool elfAccess;
	bool status;
	static User* instance;
	User(const User& obj) {}
	User() {}
public:
	static User& getInstance();
	void login();
	string getUsername() { return username; }
	bool getStatus() { return status; }
	string getType() { return type; }
};



