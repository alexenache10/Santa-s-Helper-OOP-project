#include "Logger.h"
Logger* Logger::instance = nullptr;

Logger* Logger::getInstance()
{
	if (!Logger::instance)
		Logger::instance = new Logger();
	return (Logger::instance);
}

void Logger::sendLogs(string logs)
{
	ofstream fileptr("logs.log", ios::app);
	try
	{
		if (!fileptr.is_open())
		{
			throw MyException(-1, "Eroare deschidere fisier de logs!\n");
		}
	}
	catch (MyException& obj)
	{
		cout << obj.getMessage() << " with error: " << obj.getCode();
		exit(0);
	}
	fileptr << logs << "\n";


	fileptr.close();
}