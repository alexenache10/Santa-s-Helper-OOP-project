#pragma once
#include "IComponent.h"
class Door :
    public IComponent
{
private:

public:
    void print() { std::cout << "Door"; }
};

