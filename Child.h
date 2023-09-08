#pragma once
#include <string>
#include <vector>
#include "Gift.h"
#include <list>
using namespace std;
class Child
{
private:
	string name;
	string surname;
	string birth;
	int id;
	list<string> adress;
	string behavior;
public:
	string getBirth() { return birth; }
	void setBirth(string&& newbirth) { birth = newbirth; newbirth.clear(); }
	string getName() { return name; }
	void setName(string&& newname) { name = newname; newname.clear(); }
	string getSurname() { return surname; }
	void setSurname(string&& newsurname) { surname = newsurname; newsurname.clear(); }
	string getBehavior() { return behavior; }
	string setBehavior(string newbehavior) { behavior = newbehavior; }
	list<string> getAdresslist() { return adress; }
	void addAdress(string&& newadress) { adress.push_back(newadress); newadress.clear(); }

	


};

//ostream& operator<<(ostream& out, const Child& obj)
//{
//
//}
