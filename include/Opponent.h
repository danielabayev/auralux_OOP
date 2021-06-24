#pragma once
#include "ControlPlanet.h"

class Opponent : public ControlPlanet
{
public:
    Opponent(const sf::Color& color);
    virtual ~Opponent() = default;
    void nextMove(const sf::Time& timePassed);
    void makePlanetMove(ManagePlanet* p,int todo , const sf::Time& timePassed);

private:
    std::vector<std::vector<std::pair<bool, int>>> m_planets_score;
    int m_number_of_planets;

    //private funcs
    void resetScore();
    int checkStatus(const ManagePlanet* p)const;
    void veteransBonus(const std::vector<std::vector<std::pair<bool, int>>>& old_score, const int old_planets);

    ManagePlanet* findNeighborReinforcment(const ManagePlanet* p)const;
    ManagePlanet* findProtectedPlanet()const;
    ManagePlanet* findConquer(const ManagePlanet* p, const sf::Color& color)const;

    int getValue(const ManagePlanet* p, int status)const;
    int getHealValue(const ManagePlanet* p)const;
    int getReinforcmentToValue(const ManagePlanet* p)const;
    int getConquerNewValue(const ManagePlanet* p)const;
    int getConquerConquerValue(const ManagePlanet* p)const;
    int getUpgradeValue(const ManagePlanet* p)const;
    int getReinforcmentFromValue(const ManagePlanet* p)const;
    int getNeighborValue(const ManagePlanet* p)const;

    void makeMoves(const sf::Time &timePassed);
};