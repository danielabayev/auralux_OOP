#pragma once
#include "ControlPlanet.h"

class Opponent : public ControlPlanet
{
public:
    Opponent(sf::Color color);
    virtual ~Opponent() = default;
    void nextMove();
    void resetScore();
    int checkStatus(ManagePlanet* p);
private:
    std::vector<std::vector<std::pair<bool, int>>> m_planets_score;
};
