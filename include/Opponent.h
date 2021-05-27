#pragma once
#include "ControlPlanet.h"

class Opponent : public ControlPlanet
{
public:
    Opponent(const int speed);
    virtual ~Opponent() = default;
private:
};
