#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>
//class Unit;

class Planet : public Object
{
public:
	Planet(sf::Color color, int kind, int maxLevel);
	~Planet()=default;
	virtual void draw(sf::RenderWindow &window);
	void move();
	void generateUnits();

	sf::Vector2f getCenter();
	float getRadius();

private:
	sf::Sprite m_precentBar;
	int m_health = 100;
	int m_unitToUpgrade;
	int m_currentLevel;
	int m_maxLevel;
	std::vector<std::shared_ptr<Unit>> m_units;
};