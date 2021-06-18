#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>

class Planet : public Object
{
public:
	Planet(sf::Color color, int maxLevel, sf::Vector2f pos);
	~Planet() = default;

	virtual void draw(sf::RenderWindow& window);

	void upgradePlanet();

	sf::Color getColor();
	void setColor(sf::Color);
	sf::CircleShape getShape()const;
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getCenter()const;
	float getRadius()const;
	bool getActive()const;
	int findColor(sf::Color);
	void setActive(bool Active);
	int getHealth()const;
	void setHealth(HealthAction action);
	int getCounterToUpgrade()const;
	void setCounterToUpgrade();
	void setFillBar(HealthAction action, sf::Color color);
	int getAmountToUpgrade()const;
	bool isMaxUpgrade()const;

private:
	int m_owner = 0;
	int m_health = 100;
	int m_unitToUpgrade ;
	int m_counterToUpgrade = 0;
	int m_currentLevel;
	int m_maxLevel;
	bool m_active = false;
	sf::Vector2f m_fillBarSize;
	sf::RectangleShape m_statusBar;
	sf::RectangleShape m_fillBar;
	sf::Sprite m_sprite;
};