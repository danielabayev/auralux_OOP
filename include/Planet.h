#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>
#include <iostream>

class Planet : public Object
{
public:
	Planet(sf::Color color, int maxLevel, sf::Vector2f pos);
	~Planet() = default;

	virtual void draw(sf::RenderWindow& window);

	void upgradePlanet();

	
	void setColor(sf::Color);
	
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
	void charge(sf::Color);
	void underAttack();
	void addToUpgrade();
	int getAmountOfUnits()const;
	void addUnits(int i);
	void decUnits();
	void resetUnits();

private:
	int m_owner = 0;
	int m_health = 100;
	int m_unitToUpgrade ;
	int m_counterToUpgrade = 0;
	int m_currentLevel;
	int m_amountOfUnits;
	int m_maxLevel;
	bool m_active = false;
	sf::Color m_chargeColor;
	int m_counterToCharge = 0;
	sf::Vector2f m_fillBarSize;
	sf::RectangleShape m_statusBar;
	sf::RectangleShape m_fillBar;
	sf::Sprite m_sprite;
	sf::Text m_healthText;
	sf::Text m_chargeText;
	sf::Font m_font;
};