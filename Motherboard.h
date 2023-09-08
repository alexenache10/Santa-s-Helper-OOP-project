#pragma once
#include "IComponent.h"

class Motherboard :
    public IComponent
{
private:
    std::string m_distributor;
public:
    Motherboard(std::string distributor = " ") { m_distributor = distributor; }
    void setString(std::string distributor) { m_distributor = distributor; }
    void print()
    {
        std::cout << "Motherboard";
    }
};

