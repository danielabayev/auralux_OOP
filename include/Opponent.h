#pragma once
#include "ControlPlanet.h"

class Opponent : public ControlPlanet
{
public:
    Opponent(sf::Color color);
    virtual ~Opponent() = default;
private:
};
