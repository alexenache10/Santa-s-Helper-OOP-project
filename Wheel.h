#pragma once
#include "IComponent.h"
class Wheel :
    public IComponent
{
private:
    double m_size;
    std::string m_distributor;
public:
    Wheel(double size = 0, std::string distributor= " ") : m_size(size), m_distributor(distributor){}
    double getSize() { return m_size; }
    void setSize(double size) { m_size = size; }

    void setDistributor(std::string name) { m_distributor = name; }
    std::string getDistributor() { return m_distributor; }
    void print() { std::cout << "Wheel"; }
};

