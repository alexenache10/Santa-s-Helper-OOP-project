#pragma once
#include "IComponent.h"
class bikeframe :
    public IComponent
{
public:
    void print() 
    {
        std::cout << "bikeframe";
    }
};

