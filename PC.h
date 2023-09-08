#pragma once
#include "Gift.h"
class PC : public Gift
{
public:
    PC(std::string type = " ") : Gift(type) {}
    std::string getClassType() { return "pc"; }
};

