#pragma once
#include "IComponent.h"
class Processor :
    public IComponent
{
private:
    float m_frequency;
    std::string m_distributor;
public:
    Processor(float frequency = 0, std::string distributor = " ") : m_frequency(frequency), m_distributor(distributor) {}
    float getFrequency() { return m_frequency; }
    std::string getDistributor() { return m_distributor; }

    void setFreq(float frequency) { m_frequency = frequency; }
    void setDistributor(std::string distributor) { m_distributor = distributor; }
    void print() { std::cout << "Processor"; }
   

};

