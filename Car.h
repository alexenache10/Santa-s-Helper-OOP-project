#pragma once
#include "Gift.h"
class Car :
    public Gift
{
private:
    int m_horsepower;
    std::string m_company;

public:
    Car(std::string type = " ") : Gift(type) {}
    void setHorsepower(int horsepower) { m_horsepower = horsepower; }
    void setCompany(std::string company) { m_company = company; }
    int getHorsepower() { return m_horsepower; }
    std::string getCompany() { return m_company; }
    std::string getClassType()  { return "car"; }
};

