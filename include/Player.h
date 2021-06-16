#pragma once
#include "ControlPlanet.h"

class Player : public ControlPlanet
{
public:
    Player();//
    virtual ~Player() = default;
    std::pair<bool,int> controlled()const;
    void setControlled(bool,int);
    bool checkIfBelongs(std::shared_ptr<ManagePlanet>)const;
  
private:
    std::pair<bool, int> m_controlled;
};
