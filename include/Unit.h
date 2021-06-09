#pragma once
#include "Object.h"
//#include "Planet.h"
class Planet;

class Unit : public Object
{
public:
    Unit(sf::Color color, Planet* p);
    virtual ~Unit() = default;
	sf::Vector2f calculateNewPosition(Planet* p);
	void setActive(bool Active) { m_active = Active; };
	bool getActive() { return m_active; };
	void move(Planet* p);
	void moveAround(Planet* p);
	void defineTowards(Planet* p);
	void moveTowards();
	bool checkDistance();
	void handleCollision(Planet *p);
private:
	struct line m_targetPlanet;
	struct parabola m_otherWay;
	bool m_active = false;
	float m_angle = 0;

	void defineTowards();
};
