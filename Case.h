#pragma once
#include "IComponent.h"
class Case :
    public IComponent
{
private:
    std::string m_caseType;
public:
    Case(std::string caseType = " ") : m_caseType(caseType) {}
    void setCaseType(std::string caseType) { m_caseType = caseType; }
    std::string getCaseType() { return m_caseType; }
    void print() { std::cout << "Case"; }

};

