#pragma once
#include "ControlPlanet.h"

class Opponent : public ControlPlanet
{
public:
    Opponent(sf::Color color);
    virtual ~Opponent() = default;
    void nextMove(sf::Time timePassed);
    void makePlanetMove(ManagePlanet* p,int todo , sf::Time timePassed);

private:
    std::vector<std::vector<std::pair<bool, int>>> m_planets_score;
    int m_number_of_planets;

    //private funcs
    void resetScore();
    int checkStatus(ManagePlanet* p);
    void veteransBonus(const std::vector<std::vector<std::pair<bool, int>>> old_score, const int old_planets);

    ManagePlanet* findNeighborReinforcment(ManagePlanet* p);
    ManagePlanet* findProtectedPlanet();
    ManagePlanet* findConquer(ManagePlanet* p,sf::Color color);

    int getValue(ManagePlanet* p, int status);
    int getHealValue(ManagePlanet* p);
    int getReinforcmentToValue(ManagePlanet* p);
    int getConquerNewValue(ManagePlanet* p);
    int getConquerConquerValue(ManagePlanet* p);
    int getUpgradeValue(ManagePlanet* p);
    int getReinforcmentFromValue(ManagePlanet* p);
    int getNeighborValue(ManagePlanet* p);

    void makeMoves(sf::Time timePassed);
};