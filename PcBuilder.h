#pragma once

#include <string>
#include <vector>
#include "IComponent.h"
#include <iostream>
#include "PC.h"
using namespace std;

class PcBuilder
{
private:
	string m_type;
	vector<IComponent*> componentArray;

public:
	PcBuilder() {}
	PcBuilder& setType(std::string type)
	{
		m_type = type;
		return *this;
	}
	PcBuilder& addComponent(IComponent* component)
	{
		componentArray.push_back(component);
		return *this;
	}
	PC build()
	{
		PC pc(m_type);
		pc.getComponentInstance().assign(componentArray.begin(), componentArray.end());
		return pc;
	}
};

