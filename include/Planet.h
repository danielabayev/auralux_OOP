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


	void upgradePlanet();

	sf::Color getColor();
	void setColor(sf::Color);
	sf::CircleShape getShape()const;
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getCenter()const;
	float getRadius()const;
	//int getActiveAmount()const;
	bool getActive()const;
	void setActive(bool Active);
	int getHealth()const;
	void setHealth(HealthAction action);
	int getCounterToUpgrade()const;
	void setCounterToUpgrade();
	void setFillBar(HealthAction action, sf::Color color);
	int getAmountToUpgrade()const;
	bool isMaxUpgrade()const;

private:
	//sf::Clock m_clock;
	//sf::Time m_timePassed;
	int m_owner = 0;
	int m_health = 100;
	int m_unitToUpgrade;
	int m_counterToUpgrade = 0;
	//int m_amountOfUnits;
	int m_currentLevel;
	int m_maxLevel;
	bool m_active = false;
	sf::Vector2f m_fillBarSize;
	sf::RectangleShape m_statusBar;
	sf::RectangleShape m_fillBar;
	//std::vector<std::shared_ptr<Unit>> m_units; //unique_ptr
};