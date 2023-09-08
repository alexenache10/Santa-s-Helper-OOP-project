#pragma once
#include "Gift.h"
class Scooter :
    public Gift
{
private:
    std::string m_color;
    int m_maxSpeed;
public:
    Scooter(std::string type = " ") : Gift(type) {}
    void setColor(std::string color) { m_color = color; }
    void setSpeed(int maxspeed) { m_maxSpeed = maxspeed; }
    int getMaxSpeed() { return m_maxSpeed; }
    std::string getColor() { return m_color; }
    std::string getClassType()  { return "scooter"; }
};

