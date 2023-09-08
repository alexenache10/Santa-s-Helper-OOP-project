#pragma once
#include <string>
using namespace std;
class MyException
{
private:
	string errorMessage;
	int errorCode;

public:
	MyException(int code = 0, const char* message = "") : errorCode(code), errorMessage(message) {}
	string getMessage() { return errorMessage; }
	int getCode() { return errorCode; }
};

