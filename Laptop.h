#pragma once
#include "Gift.h"
class Laptop :
    public Gift
{
private:
    std::string m_company;

public:
    Laptop(std::string type = " ") : Gift(type) {}
    void setcompany(std::string company) { m_company = company; }
    void addComponent(IComponent* component) { this->componentarray.push_back(component); }

    std::string getClassType() { return "laptop"; }
};

