#pragma once
#include "Object.h"
//#include "Planet.h"
#include <utility>
class Planet;

class Unit : public Object
{
public:
    Unit(sf::Color color, int kind, Planet* p);
    virtual ~Unit() = default;
	sf::Vector2f calculateNewPosition(Planet* p);
	void setActive(bool Active) { m_active = Active; };
	bool getActive() { return m_active; };
	void move(Planet* p);
	void moveAround(Planet* p);
	void defineTowards(Planet* p);
	void moveTowards();
	bool checkDistance();
private:
	struct line targetPlanet;
	bool m_active = false;
	std::pair<int, int> m_target_position;
	float m_angle = 0;
	//rotation/move
	//Planet* m_planet;
};
