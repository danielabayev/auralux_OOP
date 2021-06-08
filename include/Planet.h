#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>
//class Unit;



class Planet : public Object
{
public:
	Planet(sf::Color color, int maxLevel , sf::Vector2f pos);
	~Planet()=default;
	virtual void draw(sf::RenderWindow &window);
	void move(Planet p);
	void generateUnits();
	void healPlanet();
	void addToUpgrade();
	void upgradePlanet();
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getCenter();
	float getRadius();

private:
	sf::Clock m_clock;
	sf::Time m_timePassed;
	int m_owner = 0;
	sf::Sprite m_precentBar;
	int m_health = 100;
	int m_unitToUpgrade;
	int m_counterToUpgrade = 0;
	int m_amountOfUnits;
	int m_currentLevel;
	int m_maxLevel;
	bool m_active = false;
	std::vector<std::shared_ptr<Unit>> m_units;
};