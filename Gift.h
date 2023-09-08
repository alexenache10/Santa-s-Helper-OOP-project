#pragma once
#include <vector>
#include "IComponent.h"
class Gift
{
protected:
	std::vector<IComponent*> componentarray;
	std::string m_type; // packed or wrap 
public:
	Gift(std::string type = " ") : m_type(type) {}
	std::string getType() { return m_type; }
	std::vector<IComponent*>& getComponentInstance() { return componentarray; }
	virtual std::string getClassType() = 0;
};

