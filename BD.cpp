#include "BD.h"
BD* BD::instance = nullptr;
//int BD::numchildren = 0;


// m-am complicat folosind si listele de cadouri /  copii doar pentru a avea grija sa aplic concepte POO

char* printTime() {

	time_t result = time(nullptr);

	return asctime(localtime(&result));
}

void tolower(std::string& str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
}

void refresh()
{
	system("cls");
	cout << "==================== Christmas platform ====================\n";
	cout << " === Logged in as: " << User::getInstance().getUsername();
	cout << "\n === Date: " << printTime();
}




void testFile(string filename)
{
	ofstream fileptr(filename, ios::app);
	try
	{
		if (!fileptr.good())
		{
			throw new MyException(0, "Unable to open the accounts file! Closing the application.");
		}
	}
	catch (MyException& obj)
	{
		cout << obj.getMessage();
		exit(0);
	}
}

void printFileContent(string filename)
{
	ifstream fileptr(filename);
	testFile(filename);

	string line;
	while (!fileptr.eof())
	{
		getline(fileptr, line);
		cout << line << endl;
	}
	fileptr.close();
}

int getNumLines(string filename)
{
	ifstream fileptr(filename);

	string line;
	int count = 0;
	while (getline(fileptr, line))
	{
		count++;
	}

	fileptr.close();
	return count;
}

string getLine(string filename, int index)
{
	int count = 0;
	ifstream fileptr(filename);
	string line;
	while (getline(fileptr, line))
	{
		if (count == index)
		{
			fileptr.close();
			return line;
		}
		count++;
	}

	fileptr.close();
	return line;
}

vector<string> copyFileContent(string filename)
{
	vector<string> content;
	string line;

	ifstream fileptr(filename);
	while (getline(fileptr, line))
	{
		content.push_back(line);
	}

	
	fileptr.close();
	return content;
}

int findFirstPossibleId()
{
	int contor = 0;
	vector<string> filecontent = copyFileContent("childs.txt");
	

	bool ok;
	do{
		ok = true;
		for (auto& it : filecontent)
		{
			if (atoi(it.c_str()) == contor)
			{
				ok = false;
			}
		}
		if(ok==false)contor++;
	} while (ok != true);

	return contor;

}

void modifyFile(string filename, string line, int index)
{
	int count = 0;
	
	vector<string> filecontent = copyFileContent(filename);
	filecontent[index] = line;

	ofstream fileptr(filename);
	for (auto& x : filecontent)
		fileptr << x << endl;


	fileptr.close();

}



void sendLog(string action)
{
	string log;
	log = "User " + User::getInstance().getUsername() + " (type " + User::getInstance().getType() + ")";
	log += action;
	string time = printTime();
	log += " [" + time;
	log[log.size() - 1] = ']';
	Logger::getInstance()->sendLogs(log);
}

void deleteindexdata(char index, string filename)
{
	vector<string> content = copyFileContent(filename);
	ofstream fileptr(filename);
	for (auto it = content.rbegin(); it != content.rend(); ++it)
	{
		if ((*it)[0] == index)
		{
			it = std::reverse_iterator<vector<string>::iterator>(content.erase(it.base() - 1));
		}
	}

	for (auto& it : content)
	{
		fileptr << it <<endl;
	}


	fileptr.close(); 
}

char getChildId(string filename, string name)
{
	ifstream fileptr(filename);

	string line;
	while (getline(fileptr, line))
	{
		if (line.find(name) != -1)
		{
			fileptr.close();
			return line[0];
		}
	}	
}

string getChildName(string id)
{
	auto content = copyFileContent("childs.txt");
	for (int i = 0; i < content.size(); i++)
	{
		istringstream stream(content[i]);
		string childid;
		stream >> childid;
		if (id == childid)
		{
			string name;
			stream >> name;
			return name;
		}
	}
	return " ";


}

void deleteindexrow(int index, string filename)
{
	try
	{
		if (index < 0 || index > getNumLines(filename) - 1)
			throw (MyException(-1, "WARNING: Delete index out of range."));
	}

	catch (MyException& obj)
	{
		cerr << obj.getMessage() << " Error code: " << obj.getCode();
		exit(0);
	}

	vector<string> content = copyFileContent(filename);
	ofstream fileptr(filename);
	int contor = 0;

	for (auto it = content.begin(); it != content.end(); ++it)
	{
		if (contor == index)
		{
			content.erase(it);
			break;
		}
		contor++;
	}

	for (auto& it : content)
	{
		fileptr << it << endl;
	}


	fileptr.close();
}

void deleteindexadress(int index, string filename)
{
	
	vector<string> content = copyFileContent(filename);
	int contor = 0;
	for (auto& it : content)
	{
		if (atoi(it.c_str()) == index)
		{
			contor++;
		}
	}

	
	if (contor != 1)
	{
		deleteindexrow(index, filename);
		sendLog(" deleted an adress.");
		return;
	}
		
}

string verifyGiftRequirements(string giftName)
{
	vector<string> filecomponent = copyFileContent("componentstock.txt");
	
	if (giftName == "laptop")
	{
		int countProcessor = 0;
		int countMotherboard = 0;
		int countVideocard = 0;

		for (auto& it : filecomponent)
		{
			istringstream stream(it);

			string component;
			stream >> component;

			if (component == "processor")
				countProcessor++;
			if (component == "videocard")
				countVideocard++;
			if (component == "motherboard")
				countMotherboard++;
		}

		if (countProcessor != 0 && countMotherboard != 0)
		{
			if (countVideocard != 0)
				return "laptopdedicated";
			return "laptopintegraded";
		}
	}
	if (giftName == "bike")
	{
		int countBikeframe = 0;
		int countWheels = 0;

		for (auto& it : filecomponent)
		{
			istringstream stream(it);

			string component;
			stream >> component;

			if (component == "bikeframe")
				countBikeframe++;
			if (component == "wheel")
				countWheels++;
		}

		if (countBikeframe != 0 && countWheels >= 2)
		{
			return "bike";
		}
	}
	if (giftName == "car")
	{
		int countEngine = 0;
		int countWheels = 0;
		int countDoor = 0;

		for (auto& it : filecomponent)
		{
			istringstream stream(it);

			string component;
			stream >> component;

			if (component == "engine")
				countEngine++;
			if (component == "wheel")
				countWheels++;
			if (component == "door")
				countDoor++;
		}
		if (countEngine != 0 && countWheels >= 4 && countDoor >=4)
		{
			return "car";
		}
	}
	if (giftName == "pc")
	{
		int countMotherboard = 0;
		int countProcessor = 0;
		int countCase = 0;
		int countVideocard = 0;


		for (auto& it : filecomponent)
		{
			istringstream stream(it);

			string component;
			stream >> component;

			if (component == "motherboard")
				countMotherboard++;
			if (component == "processor")
				countProcessor++;
			if (component == "case")
				countCase++;
			if (component == "videocard")
				countVideocard++;
		}
		if (countMotherboard != 0 && countProcessor != 0 && countCase != 0)
		{
			if (countVideocard != 0)
			{
				return "pcdedicated";
			}
			return "pcintegrated";
		}
		
	}
	if (giftName == "scooter")
	{
		int countWheels = 0;
		int countEngine = 0;
		int countBikeframe = 0;

		for (auto& it : filecomponent)
		{
			istringstream stream(it);

			string component;
			stream >> component;

			if (component == "engine")
				countEngine++;
			if (component == "wheel")
				countWheels++;
			if (component == "bikeframe")
				countBikeframe++;
		}
		if (countEngine != 0 && countWheels >= 2 && countBikeframe !=0)
		{
			return "scooter";
		}
	}
	return " ";
}

void BD::startApplication()
{
	cout << "==================== Christmas platform ====================\n";
	User::getInstance().login();
	system("cls");
	cout << "==================== Christmas platform ====================\n";
	cout << " === Logged in as: " << User::getInstance().getUsername();
	cout << "\n === Date: " << printTime();

	cout << " === Choose an option: \n 1 - Create\n 2 - Read\n 3 - Update\n 4 - Delete\n 5 - Exit\n";
	char applicationOption = _getch();

	if (User::getInstance().getType() == "santa")
	{
		if (applicationOption == '1')
		{
			
			refresh();
			cout << " === Choose an option: \n 1 - Add child\n 2 - Add gift\n 3 - Add adress\n";
			char option = _getch();
			if (option == '1')
			{
				ofstream accountsfileptr("childs.txt", ios::app);
				testFile("childs.txt");
				int id = findFirstPossibleId(); accountsfileptr << id <<" ";
				refresh();
				string aux;
				cout << "Child's name: "; cin >> aux; accountsfileptr << aux << " ";
				cout << "Child's surname: "; cin >> aux; accountsfileptr << aux << " ";
				cout << "Child's birthdate: "; cin >> aux; accountsfileptr << aux << " ";
				cout << "Child's behavior (good / bad): ";  cin >> aux; tolower(aux); accountsfileptr << aux << " ";
				accountsfileptr << endl;
				accountsfileptr.close();

				ofstream adressfileptr("adresses.txt", ios::app);
				testFile("adresses.txt");
				cout << "Child's adress (you can add later other adresses).\n";
				adressfileptr << id << " ";
				cout << "City: "; cin >> aux; adressfileptr << aux << " ";
				cout << "Street: "; cin >> aux; adressfileptr << aux << " ";
				cout << "Number: "; cin >> aux; adressfileptr << aux << endl;
				adressfileptr.close();

				//revenire aici sa si postezi cadourile de pot fi selectate
				ofstream giftsfileptr("desiredgifts.txt", ios::app);
				testFile("desiredgifts.txt");
				giftsfileptr << id << " ";
				cout << "Child's most wanted gift: "; cin >> aux; tolower(aux); giftsfileptr << aux << " ";
				giftsfileptr << endl;
				giftsfileptr.close();
				
				sendLog(" added a child to database.");

			}
			if (option == '2')
			{
				ofstream giftsfileptr("desiredgifts.txt", ios::app);
				testFile("desiredgifts.txt");

				string aux;
				cout << "Enter the way to add the gift (id - by child's id from accounts.txt / name - by child's name from accounts.txt): ";
				cin >> aux;
				tolower(aux);

				if (aux == "id")
				{
					cout << "Enter child's id (you can find all of the ids in childs.txt file): "; cin >> aux;
					giftsfileptr << aux << " ";
					cout << "Enter the desired gift's name: "; cin >> aux; tolower(aux);
					giftsfileptr << aux << endl;

					sendLog(" added a gift.");

					
				}
				if (aux == "name")
				{
					ifstream childsfileptr("childs.txt");
					cout << "Enter child's name: "; cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, aux);
					string line;
					string word;
					string giftname;
					cout << "Enter the desired gift's name: "; cin >> giftname; tolower(giftname);
					while (!childsfileptr.eof())
					{
						getline(childsfileptr, line);

						if (line.find(aux) != -1)
						{
							istringstream stringstream(line);
							stringstream >> word;
						}
					}
					giftsfileptr << word << " " << giftname << endl;
					
					
					sendLog(" added a gift.");
				}

				giftsfileptr.close();
			}
			if (option == '3')
			{
				ofstream adressesfileptr("adresses.txt", ios::app);
				testFile("adresses.txt");

				string aux;
				cout << "Enter the way to add the adress (id - by child's id from accounts.txt / name - by child's name from accounts.txt): ";
				cin >> aux;
				tolower(aux);

				if (aux == "id")
				{
					cout << "Enter child's id (you can find all of the ids in childs.txt file): "; cin >> aux;
					adressesfileptr << aux << " ";
					cout << "Enter child's city: "; cin >> aux;
					adressesfileptr << aux << " ";
					cout << "Enter child's street name: "; cin >> aux;
					adressesfileptr << aux << " ";
					cout << "Enter child's number: "; cin >> aux;
					adressesfileptr << aux << endl;

					sendLog(" added an adress.");
				}
				if (aux == "name")
				{
					ifstream childsfileptr("childs.txt");
					cout << "Enter child's name: "; cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, aux);
					string line;
					string word;
					
					while (!childsfileptr.eof())
					{
						getline(childsfileptr, line);

						if (line.find(aux) != -1)
						{
							istringstream stringstream(line);
							stringstream >> word;
						}
					}

					adressesfileptr << word << " ";
					cout << "Enter child's city: "; cin >> aux;
					adressesfileptr << aux << " ";
					cout << "Enter child's street name: "; cin >> aux;
					adressesfileptr << aux << " ";
					cout << "Enter child's number: "; cin >> aux;
					adressesfileptr << aux << endl;

					sendLog(" added an adress.");
				}
			
			}

		}
		if (applicationOption == '2')
		{
			refresh();
			cout << " === Choose an option: \n 1 - Children\n 2 - Adresses\n 3 - Desired gifts (ID before giftname represents the ID of the child)\n";
			char option = _getch();

			if (option == '1')
			{
				printFileContent("childs.txt");
			}
			if (option == '2')
			{
				printFileContent("adresses.txt");
			}
			if (option == '3')
			{
				printFileContent("desiredgifts.txt");
			}

		}
		if (applicationOption == '3')
		{
			refresh();
			cout << " === Choose the file that you want to update: \n 1 - Children\n 2 - Adresses\n 3 - Desired gifts\n";
			char updateOption = _getch();


			string filename;
			if (updateOption == '1')
			{
				printFileContent("childs.txt");
				filename = "childs.txt";
			}
			if (updateOption == '2')
			{
				printFileContent("adresses.txt");
				filename = "adresses.txt";
			}
			if (updateOption == '3')
			{
				printFileContent("desiredgifts.txt");
				filename = "desiredgifts.txt";
			}

			string modifiedLine;
			string index;
			cout << "=== Now insert the index of the row to start modifying it [0," << getNumLines(filename)-1 << "] "; 
			cin >> index;
			cout << "\n=== You'll modify this line: "; cout << getLine(filename, atoi(index.c_str()));
			cout << "\n=== Introduce the modified sentence (please, watch the syntax): "; 
			cin.clear(); cin.ignore(INT_MAX, '\n');
			getline(cin, modifiedLine);
			modifyFile(filename, modifiedLine, atoi(index.c_str()));
			cout << "\n=== Data looks like this now:\n"; printFileContent(filename);

			sendLog(" updated a file.");

		}
		if (applicationOption == '4')
		{
			refresh();
			cout << " === Choose what you want to delete: \n 1 - Child\n 2 - Gift \n 3 - Adress (keep in mind that you can't delete an adress if only one exists)\n";
			char option = _getch();
			switch (option)
			{
				case '1':
				{
					cout << " === All data about the childs: \n";
					printFileContent("childs.txt");

					string findoption;
					cout << "\n === Enter the way you want to find a child and delete him (id / name): "; cin >> findoption;
					tolower(findoption);




					char id;
					if (findoption == "id")
					{
						cout << " === Enter the id of the child that you want to delete (take one from above): "; id = _getch();
						deleteindexdata(id, "adresses.txt");
						deleteindexdata(id, "desiredgifts.txt");
						deleteindexdata(id, "childs.txt");
						
					}
					if (findoption == "name")
					{
						string name;
						cout << " === Enter the name of the child that you want to delete: "; 	cin.clear(); cin.ignore(INT_MAX, '\n');
						getline(cin, name);
						
						id = getChildId("childs.txt", name);
						deleteindexdata(id, "childs.txt");
						deleteindexdata(id, "adresses.txt");
						deleteindexdata(id, "desiredgifts.txt");

					}

					sendLog(" deleted a child.");
					break;
				}
				case'2':
				{
					cout << " === All desired gifts by childs: \n";
					printFileContent("desiredgifts.txt");

					cout << " === Enter the index of one row from above that you want to be deleted (not that number you see as first word of every row) [0/";
					cout << getNumLines("desiredgifts.txt") - 1 << "] ";
					string rowindex; cin >> rowindex;

					deleteindexrow(atoi(rowindex.c_str()), "desiredgifts.txt");
					sendLog(" deleted a desired gift.");
					break;
				}
				case '3':
				{
					cout << " === All adresses: \n";
					printFileContent("adresses.txt");

					cout << " === Enter the index of one row from above that you want to be deleted (not that number you see as first word of every row) [0/";
					cout << getNumLines("adresses.txt") - 1 << "] ";
					cout << "\n === You can't delete an adress if it's the child's only one\n === Index: "; 
					string rowindex; cin >> rowindex;
																																																
					deleteindexadress(atoi(rowindex.c_str()), "adresses.txt");
					
					


					break;
				}

			}
		}
		if (applicationOption == '5')
		{
			exit(0);
		}
	}
	if (User::getInstance().getType() == "elf")
	{
		if (applicationOption == '1')
		{
			refresh();
			cout << " === Choose an option: \n 1 - Create gift\n 2 - Add component into stock\n 3 - Give gifts to children \n";
			char option = _getch();
			if (option == '1')
			{
				//verificam daca avem comp. necesare pentru cadoul anume, apoi le scoatem din stoc (din fisier) si adaugam cadoul in atelier (in fisier) sa il faca elfii (prelucram datele din fisierul cu cadouri)
				refresh();
				cout << " === List of gifts that can be created in the garage, their components and their option index: \n";
				cout << " === 1. Bike -  2 wheels, bikeframe\n";
				cout << " === 2. Car -  4 wheels, engine, 4 doors\n";
				cout << " === 3. Laptop -  processor, motherboard, videocard (optional)\n";
				cout << " === 4. PC - processor, motherboard, videocard (optional), case\n";
				cout << " === 5. Scooter - bikeframe, engine, 2 wheels\n";

				char giftOption = _getch();
				switch (giftOption)
				{
				case '1':
				{
					string result = verifyGiftRequirements("bike");
					if (result == "bike") // daca nu ar fi "bike" ci un string gol ar insemna ca nu avem comp. necesare
					{
						ofstream giftstockptr("giftdata.txt", ios::app);
						giftstockptr << "bike" << " ";

						int countWheels = 2;
						int countBikeframe = 1;

						auto componentfilevector = copyFileContent("componentstock.txt");
						while (countBikeframe != 0 && countWheels != 0)
						{
							for (auto it = componentfilevector.begin(); it != componentfilevector.end(); ++it)
							{
								istringstream stream(*it);
								string componentname;
								stream >> componentname;
								if (componentname == "wheel" && countWheels != 0)
								{
									string dimension;
									string distributor;
									stream >> dimension >> distributor;
									giftstockptr << "wheel" << " " << dimension << " " << distributor << " ";
									*it = " ";
									countWheels--;
								}
								if (componentname == "bikeframe" && countBikeframe != 0)
								{
									giftstockptr << "bikeframe" << " ";
									*it = " ";
									countBikeframe--;
								}

							}
						}
						giftstockptr << endl;

						ofstream fileptr("componentstock.txt");
						for (auto& it : componentfilevector)
						{
							if (it != " ")
								fileptr << it << endl;
						}
						fileptr.close();
						giftstockptr.close();
						componentfilevector.erase(componentfilevector.begin(), componentfilevector.end());

					}
					string log = " created a bike using stock components that is ready to be sent to a child.";
					sendLog(log);
					break;
				}
				case '2':
				{
					string result = verifyGiftRequirements("car");
					if (result == "car")
					{
						ofstream giftstockptr("giftdata.txt", ios::app);
						giftstockptr << "car" << " ";

						int countWheels = 4;
						int countDoors = 4;
						int countEngine = 1;


						auto componentfilevector = copyFileContent("componentstock.txt");
						while (countWheels != 0 && countDoors != 0 && countEngine != 0)
						{
							for (auto it = componentfilevector.begin(); it != componentfilevector.end(); ++it)
							{
								istringstream stream(*it);
								string componentname;
								stream >> componentname;
								if (componentname == "wheel" && countWheels != 0)
								{
									string dimension;
									string distributor;
									stream >> dimension >> distributor;
									giftstockptr << "wheel" << " " << dimension << " " << distributor << " ";
									*it = " ";
									countWheels--;
								}
								if (componentname == "engine" && countEngine != 0)
								{

									string capacity;
									stream >> capacity;
									giftstockptr << "engine" << " " << capacity << " ";
									*it = " ";
									countEngine--;
								}
								if (componentname == "door" && countDoors != 0)
								{
									giftstockptr << "door" << " ";
									*it = " ";
									countDoors--;
								}

							}
						}

						giftstockptr << endl;
						ofstream fileptr("componentstock.txt");
						for (auto& it : componentfilevector)
						{
							if (it != " ")
								fileptr << it << endl;
						}
						fileptr.close();
						giftstockptr.close();
						componentfilevector.erase(componentfilevector.begin(), componentfilevector.end());

					}
					string log = " created a car using stock components that is ready to be sent to a child.";
					sendLog(log);
					break;
				}
				case '3':
				{
					string result = verifyGiftRequirements("laptop");
					if (result == "laptopdedicated" || result == "laptopintegrated")
					{
						ofstream giftstockptr("giftdata.txt", ios::app);
						giftstockptr << "laptop" << " ";

						int countMotherboard = 1;
						int countProcessor = 1;
						int countVideocard = 1;

						auto componentfilevector = copyFileContent("componentstock.txt");
						while (countMotherboard != 0 && countProcessor != 0)
						{
							for (auto it = componentfilevector.begin(); it != componentfilevector.end(); ++it)
							{
								istringstream stream(*it);
								string componentname;
								stream >> componentname;

								if (componentname == "motherboard" && countMotherboard != 0)
								{
									string distributor;
									stream >> distributor;
									giftstockptr << "motherboard " << "distributor " << distributor << " ";
									*it = " ";
									countMotherboard--;
								}
								if (componentname == "processor" && countProcessor != 0)
								{
									string frequency;
									string distributor;
									stream >> frequency >> distributor;
									giftstockptr << "processor " << "frequency " << frequency << " distributor " << distributor << " ";
									*it = " ";
									countProcessor--;
								}
								if (componentname == "videocard" && countVideocard != 0)
								{
									string ramsize;
									string name;
									stream >> ramsize >> name;
									giftstockptr << "videocard " << "ramsize " << ramsize << " name " << name << " ";
									*it = " ";
									countVideocard--;
								}

							}

						}
						giftstockptr << endl;
						ofstream fileptr("componentstock.txt");
						for (auto& it : componentfilevector)
						{
							if (it != " ")
								fileptr << it << endl;
						}
						fileptr.close();
						giftstockptr.close();
						componentfilevector.erase(componentfilevector.begin(), componentfilevector.end());

					}
					string log = " created a laptop using stock components that is ready to be sent to a child.";
					sendLog(log);
					break;
				}
				case '4':
				{
					string result = verifyGiftRequirements("pc");
					if (result == "pcintegrated" || result == "pcdedicated")
					{
						ofstream giftstockptr("giftdata.txt", ios::app);
						giftstockptr << "pc" << " ";

						int countMotherboard = 1;
						int countProcessor = 1;
						int countVideocard = 1;
						int countCase = 1;

						auto componentfilevector = copyFileContent("componentstock.txt");
						while (countMotherboard != 0 && countProcessor != 0 && countCase != 0)
						{
							for (auto it = componentfilevector.begin(); it != componentfilevector.end(); ++it)
							{
								istringstream stream(*it);
								string componentname;
								stream >> componentname;

								if (componentname == "motherboard" && countMotherboard != 0)
								{
									string distributor;
									stream >> distributor;
									giftstockptr << "motherboard " << "distributor " << distributor << " ";
									*it = " ";
									countMotherboard--;
								}
								if (componentname == "processor" && countProcessor != 0)
								{
									string frequency;
									string distributor;
									stream >> frequency >> distributor;
									giftstockptr << "processor " << "frequency " << frequency << " distributor " << distributor << " ";
									*it = " ";
									countProcessor--;
								}
								if (componentname == "videocard" && countVideocard != 0)
								{
									string ramsize;
									string name;
									stream >> ramsize >> name;
									giftstockptr << "videocard " << "ramsize " << ramsize << " name " << name << " ";
									*it = " ";
									countVideocard--;
								}
								if (componentname == "case" && countCase != 0)
								{
									string type;
									stream >> type;
									giftstockptr << "case " << "type " << type << " ";
									*it = " ";
									countCase--;
								}

							}

						}
						giftstockptr << endl;
						ofstream fileptr("componentstock.txt");
						for (auto& it : componentfilevector)
						{
							if (it != " ")
								fileptr << it << endl;
						}
						fileptr.close();
						giftstockptr.close();
						componentfilevector.erase(componentfilevector.begin(), componentfilevector.end());
					}
					string log = " created a pc using stock components that is ready to be sent to a child.";
					sendLog(log);
					break;
				}
				case '5':
				{
					string result = verifyGiftRequirements("scooter");
					if (result == "scooter")
					{
						ofstream giftstockptr("giftdata.txt", ios::app);
						giftstockptr << "scooter" << " ";

						int countWheels = 2;
						int countEngine = 1;
						int countBikeframe = 1;

						auto componentfilevector = copyFileContent("componentstock.txt");
						while (countWheels != 0 && countEngine != 0 && countBikeframe != 0)
						{
							for (auto it = componentfilevector.begin(); it != componentfilevector.end(); ++it)
							{
								istringstream stream(*it);
								string componentname;
								stream >> componentname;

								if (componentname == "wheel" && countWheels != 0)
								{
									string dimension;
									string distributor;
									stream >> dimension >> distributor;
									giftstockptr << "wheel" << " " << dimension << " " << distributor << " ";
									*it = " ";
									countWheels--;
								}

								if (componentname == "engine" && countEngine != 0)
								{
									string capacity;
									stream >> capacity;
									giftstockptr << "engine" << " " << capacity << " ";
									*it = " ";
									countEngine--;
								}

								if (componentname == "bikeframe" && countBikeframe != 0)
								{
									giftstockptr << "bikeframe" << " ";
									*it = " ";
									countBikeframe--;
								}
							}
						}
						giftstockptr << endl;
						ofstream fileptr("componentstock.txt");
						for (auto& it : componentfilevector)
						{
							if (it != " ")
								fileptr << it << endl;
						}
						fileptr.close();
						giftstockptr.close();
						componentfilevector.erase(componentfilevector.begin(), componentfilevector.end());

					}
					string log = " created a scooter using stock components that is ready to be sent to a child.";
					sendLog(log);
					break;
				}
				}
			}
			if (option == '2')
			{
				refresh();
				cout << " === List of components you can add to stock: \n";
				cout << " === bikeframe\n";
				cout << " === case\n";
				cout << " === door\n";
				cout << " === motherboard\n";
				cout << " === engine\n";
				cout << " === processor\n";
				cout << " === videocard\n";
				cout << " === wheel\n";

				string componentName;
				cout << " === Introduce the component name that you want to add into stock: "; cin >> componentName; tolower(componentName);

				ofstream fileptr("componentstock.txt", ios::app);
				fileptr << componentName << " ";


				if (componentName == "bikeframe")
				{
					fileptr << endl;
				}
				if (componentName == "case")
				{
					string caseType;
					cout << " === Now introduce type of the case: ";  cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, caseType);
					fileptr << caseType << endl;
				}
				if (componentName == "door")
				{
					fileptr << endl;
				}
				if (componentName == "motherboard")
				{
					string distributor;
					cout << " === Now introduce the moatherboard's distributor: ";  cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, distributor);
					fileptr << distributor << endl;
				}
				if (componentName == "engine")
				{
					string capacity;
					cout << " === Now introduce the engine's capacity: "; cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, capacity);
					fileptr << capacity << endl;
				}
				if (componentName == "processor")
				{
					string frequency;
					string distributor;
					cout << " === Now introduce the processor's frequency and distributor.\n === Frequency: "; cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, frequency);
					cout << " === Distributor: "; getline(cin, distributor);
					fileptr << frequency << " " << distributor << endl;
				}
				if (componentName == "videocard")
				{
					string ramsize;
					string name;

					cout << " === Now introduce the videocard's ram size and name.\n === Ram size: "; cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, ramsize);
					cout << " === Name: "; getline(cin, name);
					fileptr << ramsize << " " << name << endl;
				}
				if (componentName == "wheel")
				{
					string size;
					string distributor;

					cout << " === Now introduce the wheel's size and distributor.\n === Size: "; cin.clear(); cin.ignore(INT_MAX, '\n'); getline(cin, size);
					cout << " === Distributor: "; getline(cin, distributor);
					fileptr << size << " " << distributor << endl;

				}


				string log = " added component ";
				log += componentName;
				log += " to database.";
				sendLog(log);

				fileptr.close();
			}
			if (option == '3')
			{
				list<Gift*> giftCreated;

				auto garagegiftV = copyFileContent("giftdata.txt");
				auto desiredgiftV = copyFileContent("desiredgifts.txt");
				for (auto& it : garagegiftV)
				{
					istringstream stream(it);

					string word;
					stream >> word;
					if (word == "laptop")
					{
						IComponent* componentProcessor = FactoryComponents::getType(FactoryComponents::Types::Processor);
						IComponent* componentMotherboard = FactoryComponents::getType(FactoryComponents::Types::Motherboard);
						IComponent* componentVideocard = FactoryComponents::getType(FactoryComponents::Types::Videocard);

						Processor* processorPtr = dynamic_cast<Processor*>(componentProcessor);
						Motherboard* motherboardPtr = dynamic_cast<Motherboard*>(componentMotherboard);
						Videocard* videocardPtr = dynamic_cast<Videocard*>(componentVideocard);

						while (stream >> word)
						{
							if (word == "motherboard")
							{
								stream >> word;
								stream >> word;
								motherboardPtr->setString(word);
							}
							if (word == "processor")
							{

								stream >> word;
								stream >> word;
								processorPtr->setFreq(atof(word.c_str()));
								stream >> word;
								stream >> word;
								processorPtr->setDistributor(word);
							}
							if (word == "videocard")
							{
								stream >> word;
								stream >> word;
								videocardPtr->setRamSize(atoi(word.c_str()));
								stream >> word;
								stream >> word;
								videocardPtr->setName(word);
							}
						}

						Builder<Laptop> laptopBuilder;
						laptopBuilder.addComponent(componentProcessor);
						laptopBuilder.addComponent(componentMotherboard);
						laptopBuilder.addComponent(componentVideocard);
						giftCreated.push_back(laptopBuilder.build());

					}

					if (word == "pc")
					{

						IComponent* componentCase = FactoryComponents::getType(FactoryComponents::Types::Case);
						IComponent* componentProcessor = FactoryComponents::getType(FactoryComponents::Types::Processor);
						IComponent* componentMotherboard = FactoryComponents::getType(FactoryComponents::Types::Motherboard);
						IComponent* componentVideocard = FactoryComponents::getType(FactoryComponents::Types::Videocard);

						Processor* processorPtr = dynamic_cast<Processor*>(componentProcessor);
						Motherboard* motherboardPtr = dynamic_cast<Motherboard*>(componentMotherboard);
						Videocard* videocardPtr = dynamic_cast<Videocard*>(componentVideocard);
						Case* casePtr = dynamic_cast<Case*>(componentCase);

						while (stream >> word)
						{
							if (word == "motherboard")
							{
								stream >> word;
								stream >> word;
								motherboardPtr->setString(word);
							}
							if (word == "processor")
							{

								stream >> word;
								stream >> word;
								processorPtr->setFreq(atof(word.c_str()));
								stream >> word;
								stream >> word;
								processorPtr->setDistributor(word);
							}
							if (word == "videocard")
							{
								stream >> word;
								stream >> word;
								videocardPtr->setRamSize(atoi(word.c_str()));
								stream >> word;
								stream >> word;
								videocardPtr->setName(word);
							}

							if (word == "case")
							{
								stream >> word;
								stream >> word;
								casePtr->setCaseType(word);
							}

						}

						Builder<PC> pcbuilder;
						pcbuilder.addComponent(componentCase);
						pcbuilder.addComponent(componentMotherboard);
						pcbuilder.addComponent(componentProcessor);
						pcbuilder.addComponent(componentVideocard);
						giftCreated.push_back(pcbuilder.build());
					}

					if (word == "bike")
					{
						IComponent* componentBikeframe = FactoryComponents::getType(FactoryComponents::Types::bikeframe);

						bikeframe* bikeframePtr = dynamic_cast<bikeframe*>(componentBikeframe);

						Builder<Bike> bikebuilder;
						bikebuilder.addComponent(componentBikeframe);
						while (stream >> word)
						{
							if (word == "wheel")
							{
								IComponent* componentWheel = FactoryComponents::getType(FactoryComponents::Types::Wheel);
								Wheel* wheelPtr = dynamic_cast<Wheel*>(componentWheel);

								stream >> word;
								wheelPtr->setSize(atof(word.c_str()));
								stream >> word;
								wheelPtr->setDistributor(word);

								bikebuilder.addComponent(componentWheel);
							}

						}

						giftCreated.push_back(bikebuilder.build());
					}

					if (word == "car")
					{
						IComponent* componentEngine = FactoryComponents::getType(FactoryComponents::Types::Engine);
						Engine* enginePtr = dynamic_cast<Engine*>(componentEngine);

						Builder<Car> carbuilder;

						while (stream >> word)
						{
							if (word == "door")
							{
								IComponent* componentDoor = FactoryComponents::getType(FactoryComponents::Types::Door);
								carbuilder.addComponent(componentDoor);
							}

							if (word == "engine")
							{
								stream >> word;
								enginePtr->setCapacity(atof(word.c_str()));

							}

							if (word == "wheel")
							{
								IComponent* componentWheel = FactoryComponents::getType(FactoryComponents::Types::Wheel);
								Wheel* wheelPtr = dynamic_cast<Wheel*>(componentWheel);
								stream >> word;
								wheelPtr->setSize(atof(word.c_str()));
								stream >> word;
								wheelPtr->setDistributor(word);



								carbuilder.addComponent(componentWheel);
							}
						}

						carbuilder.addComponent(componentEngine);
						giftCreated.push_back(carbuilder.build());
					}

					if (word == "scooter")
					{
						IComponent* componentBikeframe = FactoryComponents::getType(FactoryComponents::Types::bikeframe);
						IComponent* componentEngine = FactoryComponents::getType(FactoryComponents::Types::Engine);
						Engine* enginePtr = dynamic_cast<Engine*>(componentEngine);
						bikeframe* bikeframePtr = dynamic_cast<bikeframe*>(componentBikeframe);




						Builder<Scooter> scooterbuilder;
						scooterbuilder.addComponent(componentBikeframe);
						while (stream >> word)
						{
							if (word == "engine")
							{
								stream >> word;
								enginePtr->setCapacity(atof(word.c_str()));
							}
							if (word == "wheel")
							{
								IComponent* componentWheel = FactoryComponents::getType(FactoryComponents::Types::Wheel);
								Wheel* wheelPtr = dynamic_cast<Wheel*>(componentWheel);
								stream >> word;
								wheelPtr->setSize(atof(word.c_str()));
								stream >> word;
								wheelPtr->setDistributor(word);
								scooterbuilder.addComponent(componentWheel);

							}
						}

						scooterbuilder.addComponent(componentEngine);

						giftCreated.push_back(scooterbuilder.build());
					}



				}

				for (auto& desiredIt : desiredgiftV)
				{
					istringstream stream(desiredIt);

					string giftName;
					string id;
					stream >> id;
					stream >> giftName;

					string childName = getChildName(id);

					if (giftName == "bike") // giftname = cadoul dorit de copil
					{
						bool ok = false;
						for (auto& stockIt : giftCreated)
						{

							if (stockIt->getClassType() == "bike")
							{

								Bike* bikeptr = dynamic_cast<Bike*>(stockIt);
								ok = true;
								cout << "Sent bike to " << childName << "." << endl;

								// am trimis cadoul, il stergem din lista lui de dorinte + atelier

								auto desiredgiftv = copyFileContent("desiredgifts.txt");
								auto giftdatav = copyFileContent("giftdata.txt");

								for (auto& it : desiredgiftv)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;
									stream >> giftname;


									if (giftname == "bike")
									{
										it = " ";
										break;
									}
								}

								for (auto& it : giftdatav)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;

									if (giftname == "bike")
									{
										it = " ";
										break;
									}

								}


								ofstream desiredgiftptr("desiredgifts.txt");
								ofstream giftdataptr("giftdata.txt");

								for (auto& it : desiredgiftv)
									if (it != " ")desiredgiftptr << it<<endl;
								for (auto& it : giftdatav)
									if (it != " ") giftdataptr << it<<endl;

								desiredgiftptr.close();
								giftdataptr.close();
								break;
							}
						}


						if (ok == true)
						{
							string log = " send a bike gift to ";
							log += childName;
							log += ".";
							sendLog(log);
						}
					}
					if (giftName == "scooter") 
					{
						bool ok = false;
						for (auto& stockIt : giftCreated)
						{

							if (stockIt->getClassType() == "scooter")
							{

								Scooter* bikeptr = dynamic_cast<Scooter*>(stockIt);
								ok = true;
								cout << "Sent scooter to " << childName << "." << endl;


								auto desiredgiftv = copyFileContent("desiredgifts.txt");
								auto giftdatav = copyFileContent("giftdata.txt");

								for (auto& it : desiredgiftv)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;
									stream >> giftname;


									if (giftname == "scooter")
									{
										it = " ";
										break;
									}
								}

								for (auto& it : giftdatav)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;

									if (giftname == "scooter")
									{
										it = " ";
										break;
									}
								}


								ofstream desiredgiftptr("desiredgifts.txt");
								ofstream giftdataptr("giftdata.txt");

								for (auto& it : desiredgiftv)
									if (it != " ")desiredgiftptr << it<<endl;
								for (auto& it : giftdatav)
									if (it != " ") giftdataptr << it<<endl;

								desiredgiftptr.close();
								giftdataptr.close();

								break;
							}
						}


						if (ok == true)
						{
							string log = " send a scooter gift to ";
							log += childName;
							log += ".";
							sendLog(log);
						}
					}
					if (giftName == "car")
					{
						bool ok = false;
						for (auto& stockIt : giftCreated)
						{

							if (stockIt->getClassType() == "car")
							{

								Car* bikeptr = dynamic_cast<Car*>(stockIt);
								ok = true;
								cout << "Sent car to " << childName << "." << endl;

								

								auto desiredgiftv = copyFileContent("desiredgifts.txt");
								auto giftdatav = copyFileContent("giftdata.txt");

								for (auto& it : desiredgiftv)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;
									stream >> giftname;


									if (giftname == "car")
									{
										it = " ";
										break;
									}
								}

								for (auto& it : giftdatav)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;

									if (giftname == "car")
									{
										it = " ";
										break;
									}
								}


								ofstream desiredgiftptr("desiredgifts.txt");
								ofstream giftdataptr("giftdata.txt");

								for (auto& it : desiredgiftv)
									if (it != " ")desiredgiftptr << it<<endl;
								for (auto& it : giftdatav)
									if (it != " ") giftdataptr << it<<endl;

								desiredgiftptr.close();
								giftdataptr.close(); break;
							}
						}


						if (ok == true)
						{
							string log = " sent a car gift to ";
							log += childName;
							log += ".";
							sendLog(log);
						}
					}
					if (giftName == "laptop")
					{
						bool ok = false;
						for (auto& stockIt : giftCreated)
						{

							if (stockIt->getClassType() == "laptop")
							{

								Laptop* bikeptr = dynamic_cast<Laptop*>(stockIt);
								ok = true;
								cout << "Sent laptop to " << childName << "." << endl;



								auto desiredgiftv = copyFileContent("desiredgifts.txt");
								auto giftdatav = copyFileContent("giftdata.txt");

								for (auto& it : desiredgiftv)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;
									stream >> giftname;


									if (giftname == "laptop")
									{
										it = " ";
										break;
									}
								}

								for (auto& it : giftdatav)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;

									if (giftname == "laptop")
									{
										it = " ";
										break;
									}
								}


								ofstream desiredgiftptr("desiredgifts.txt");
								ofstream giftdataptr("giftdata.txt");

								for (auto& it : desiredgiftv)
									if (it != " ")desiredgiftptr << it<<endl;
								for (auto& it : giftdatav)
									if (it != " ") giftdataptr << it<<endl;

								desiredgiftptr.close();
								giftdataptr.close(); break;
							}
						}


						if (ok == true)
						{
							string log = " sent a laptop gift to ";
							log += childName;
							log += ".";
							sendLog(log);
						}
					}
					if (giftName == "pc")
					{
						bool ok = false;
						for (auto& stockIt : giftCreated)
						{

							if (stockIt->getClassType() == "pc")
							{

								Car* bikeptr = dynamic_cast<Car*>(stockIt);
								ok = true;
								cout << "Sent PC to " << childName << "." << endl;



								auto desiredgiftv = copyFileContent("desiredgifts.txt");
								auto giftdatav = copyFileContent("giftdata.txt");

								for (auto& it : desiredgiftv)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;
									stream >> giftname;


									if (giftname == "pc")
									{
										it = " ";
										break;
									}
								}

								for (auto& it : giftdatav)
								{
									istringstream stream(it);
									string giftname;
									stream >> giftname;

									if (giftname == "pc")
									{
										it = " ";
										break;
									}
								}


								ofstream desiredgiftptr("desiredgifts.txt");
								ofstream giftdataptr("giftdata.txt");

								for (auto& it : desiredgiftv)
									if (it != " ")desiredgiftptr << it <<endl;
								for (auto& it : giftdatav)
									if (it != " ") giftdataptr << it<<endl;

								desiredgiftptr.close();
								giftdataptr.close(); break;
							}
						}


						if (ok == true)
						{
							string log = " sent a pc gift to ";
							log += childName;
							log += ".";
							sendLog(log);
						}
					}
}

			}
		}
		if (applicationOption == '2')
		{
			cout <<  " == = Choose an option : \n 1 - Current created gifts\n 2 - Components stock\n";
			char readoption = _getch();
			if (readoption == '1')
			{
				auto createdgiftsv = copyFileContent("giftdata.txt");
				for (auto& it : createdgiftsv)
					cout << it << endl;
			}
			if (readoption == '2')
			{
				auto createdgiftsv = copyFileContent("componentstock.txt");
				for (auto& it : createdgiftsv)
					cout << it << endl;
			}
		}
	}
}

BD* BD::getInstance()
{
	if (!BD::instance)
		BD::instance = new BD();
	return (BD::instance);
}
