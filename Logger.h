#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "MyException.h"
using namespace std;
class Logger
{
private:
	static Logger* instance;


public:
	static void sendLogs(string logs);
	static Logger* getInstance();
};

