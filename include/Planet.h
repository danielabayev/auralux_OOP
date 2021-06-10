#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>
//class Unit;

class Planet : public Object
{
public:
	Planet(sf::Color color, int maxLevel, sf::Vector2f pos);
	~Planet() = default;

	virtual void draw(sf::RenderWindow& window);

	//void move(Planet p);
	//void generateUnits();

	void healPlanet(int &m_amountOfUnits, std::vector<std::shared_ptr<Unit>>& m_units);
	void addToUpgrade(int &m_amountOfUnits, std::vector<std::shared_ptr<Unit>>& m_units);
	void upgradePlanet();

	sf::CircleShape getShape()const;
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getCenter()const;
	float getRadius()const;
	//int getActiveAmount()const;
	bool getActive()const;
	void setActive(bool Active);

private:
	//sf::Clock m_clock;
	//sf::Time m_timePassed;
	int m_owner = 0;
	sf::Sprite m_precentBar;
	int m_health = 100;
	int m_unitToUpgrade;
	int m_counterToUpgrade = 0;
	//int m_amountOfUnits;
	int m_currentLevel;
	int m_maxLevel;
	bool m_active = false;
	//std::vector<std::shared_ptr<Unit>> m_units; //unique_ptr
};