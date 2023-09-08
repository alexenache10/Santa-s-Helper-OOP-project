#include "User.h"

User* User::instance = nullptr;


void lowcases(std::string& str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
}


User& User::getInstance()
{
	if (!User::instance)
		User::instance = new User();
	return (*User::instance);
}


bool verifyUsername(string username)
{
	ifstream filePtr("accounts.txt");

	string line;
	while (!filePtr.eof())
	{
		getline(filePtr, line);
		istringstream linestream(line);
		
		string fileusername;
		linestream >> fileusername;

		if (fileusername == username)
			return true;
	}
	filePtr.close();
	return false;
}

bool verifyType(string username)
{
	ifstream filePtr("accounts.txt");

	string line;
	while (!filePtr.eof())
	{
		getline(filePtr, line);
		if (line.find(username) != -1 && line.find("Santa"))
		{
			filePtr.close();
			return true;
		}
		}
	filePtr.close();
	return false;
}

bool verifySanta()
{
	ifstream filePtr("accounts.txt");

	string line;
	while (!filePtr.eof())
	{
		getline(filePtr, line);
		if (line.find("santa") != -1)
		{
			filePtr.close();
			return true;
		}

	}
	return false;
}


bool verifyPassword(string username, string password)
{
	ifstream filePtr("accounts.txt");

	string line;
	while (!filePtr.eof())
	{
		getline(filePtr, line);
		if (line.find(username) != -1)
		{
			istringstream newStream(line);
			string word;
			newStream >> word;
			newStream >> word;
			if (word == password)
			{
				filePtr.close();
				return true;
			}
			else
			{
				filePtr.close();
				return false;
			}
		}
	}
}

void setType(string& newtype, string username)
{
	ifstream filePtr("accounts.txt");
	string line;

	while (!filePtr.eof())
	{
		getline(filePtr, line);
		if (line.find(username) != -1)
		{
			int last_space_pos = line.find_last_of(' ');
			string word = line.substr(last_space_pos + 1);
			newtype = word;
			filePtr.close();
			return;
		}
	}
}





void User::login()
{
	//cout << "====================== User platform ======================\n";
	if (status != true)
	{
		ofstream filePtr("accounts.txt", ios_base::app);
		try
		{

			if (!filePtr.good())
			{
				throw MyException(0, "Unable to open accounts.txt file!");
				exit(0);
			}
		}
		catch (MyException& obj)
		{
			cerr << obj.getMessage() << " Error code: " << obj.getCode() << endl;
		}

		cout << "Introduce your username to log in to the Christmas platform!";
		cout << "\nUsername: "; cin >> username;
		try
		{
			if (verifyUsername(username) == false)
			{
				throw MyException(-1, "Username not found in accounds file, create a new one!");
			}
			else
			{
				setType(type, username);
			}
		}
		catch (MyException& obj)
		{
			cerr << obj.getMessage();
			cerr << "\nEnter account type: "; cin >> type;
			lowcases(type);
			if (type == "santa" && verifySanta() == true)
			{
				cerr << "Santa's account already exists, you will create an elf one then!";
				type = "elf";
			}
			cerr << "Enter a password for the account in order to be created!\nPassword: ";
			cin >> password;

			if (type == "santa")
				santaAccess = true;
			else
				elfAccess = true;

			if (type == "santa" || type == "elf")
			{
				filePtr << username << " " << password << " " << type << endl;
				status = true;
			}
			else
			{
				cerr << "Only santa and his elf can access the platform!";
				filePtr.close();
				exit(0);
			}

			if (type == "santa")
				santaAccess = true;
			else
				elfAccess = true;
			filePtr.close();
			return;
		}

		cout << "Introduce your password: ";
		cin >> password;

		int wrongCounter = 0;
		while (wrongCounter < 3)
		{
			if (verifyPassword(username, password) == false)
			{
				wrongCounter++;
				cerr << "You typed a wrong password, you are at the " << wrongCounter << " /3 attempt\n";
				if (wrongCounter != 3)
				{
					cerr << "Introduce your password: ";
					cin >> password;
				}
			}
			if (wrongCounter != 3 && verifyPassword(username, password) == true)
			{
				break;
			}
			if (wrongCounter == 3)
			{
				filePtr.close();
				cerr << "You've reached attempt 3/3, you were kicked out from the platform!";
				exit(0);
			}
		}
		
		if(!(type == "elf" || type == "santa"))
		{
			cerr << "Only santa and his elf can access the platform!";
			filePtr.close();
			exit(0);
		}
		if (type == "santa")
			santaAccess = true;
		else
			elfAccess = true;
		status = true;
		filePtr.close();
	}
}