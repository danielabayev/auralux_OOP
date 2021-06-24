#pragma once
#include "Object.h"
//#include "Planet.h"
class Planet;

class Unit : public Object
{
public:
    Unit(sf::Color color, Planet* p);
    virtual ~Unit() = default;
	sf::Vector2f calculateNewPosition(const Planet& p);
	sf::Vector2f move(const Planet& p, const sf::Time& timePassed , int angle);
	void moveAround(const Planet& p,const sf::Time& timePassed , int angle);
	void defineTowards(const Planet& p);
	sf::Vector2f moveTowards(const sf::Time& timePassed);

	//gets sets
	bool inUse()const;
	void setInUse(bool used);
	void setColor(const sf::Color&);
	void setActive(bool Active);
	bool getActive()const { return m_active; };
	void setWaitToMove(bool moved);
	bool getWaitToMove()const;
	sf::Vector2f getTargetPlanet()const;
	int getTargetIndex()const;

private:
	struct line m_targetPlanet;
	bool m_active = false;
	float m_angle = 0;
	bool m_waitToMove = false;
	sf::Clock m_clock;
	sf::Time m_timePassed;

	void defineTowards();
	bool checkDistance();
};
