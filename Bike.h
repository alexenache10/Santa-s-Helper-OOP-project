#pragma once
#include "Gift.h"
class Bike :
    public Gift
{
private:
    std::string m_color;
public:
    Bike(std::string type = " ", std::string color = " ") : Gift(type) { m_color = color; }
    std::string getColor() { return m_color; }
    std::string getClassType()  { return "bike"; }
};

