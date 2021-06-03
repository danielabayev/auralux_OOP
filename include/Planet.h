#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>
//class Unit;

class Planet : public Object
{
public:
	Planet(sf::Color color, int kind, int maxLevel,int owner);
	~Planet()=default;
	virtual void draw(sf::RenderWindow &window);
	void move(Planet p);
	void generateUnits();

	void setPosition(sf::Vector2f newPosition);

	sf::Vector2f getCenter();
	float getRadius();

private:
	int m_owner = 0;
	sf::Sprite m_precentBar;
	int m_health = 100;
	int m_unitToUpgrade;
	int m_currentLevel;
	int m_maxLevel;
	std::vector<std::shared_ptr<Unit>> m_units;
};