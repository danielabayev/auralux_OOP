#pragma once
#include "Object.h"
//#include "Planet.h"
class Planet;

class Unit : public Object
{
public:
    Unit(sf::Color color, Planet* p);
    virtual ~Unit() = default;
	sf::Vector2f calculateNewPosition(Planet p);
	sf::Vector2f move(Planet p , sf::Time timePassed);
	void moveAround(Planet p , sf::Time timePassed);
	void defineTowards(Planet p);
	sf::Vector2f moveTowards(sf::Time timePassed);
	bool checkDistance();
	void handleCollision(Planet *p);

	bool inUse()const;
	void setInUse(bool used);
	void setColor(sf::Color);
	void setActive(bool Active);
	bool getActive() { return m_active; };
	void setWaitToMove(bool moved);
	bool getWaitToMove()const;
	sf::Vector2f getTargetPlanet();
private:
	struct line m_targetPlanet;
	struct parabola m_otherWay;
	bool m_active = false;
	float m_angle = 0;
	bool m_waitToMove = false;
	sf::Clock m_clock;
	sf::Time m_timePassed;

	void defineTowards();
};
