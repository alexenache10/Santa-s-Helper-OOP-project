#pragma once
#include "IComponent.h"
class Videocard :
    public IComponent
{
private:
    int m_ramSize;
    std::string m_name;
public:
    Videocard(int ramSize = 0, std::string name = " ") { m_ramSize = ramSize; m_name = name; }
    void setRamSize(int ramSize) { m_ramSize = ramSize; }
    void setName(std::string name) { m_name = name; }
    int getRamSize() { return m_ramSize; }
    std::string getName() { return m_name; }
    void print() { std::cout << "Videocard"; }
};

