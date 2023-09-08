#pragma once
#include "IComponent.h"
class Engine :
    public IComponent
{
private:
    float m_capacity;
public:
    Engine(float capacity = 0) : m_capacity(capacity) {}
    float getCapacity() { return m_capacity; }
    void setCapacity(float capacity) { m_capacity = capacity; }
    void print() { std::cout << "Engine"; }



};

