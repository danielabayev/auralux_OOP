#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>
#include <iostream>
#include "Music.h"

class Planet : public Object
{
public:
	Planet(sf::Color color, int maxLevel, sf::Vector2f pos , int index);
	~Planet() = default;

	virtual void draw(sf::RenderWindow& window);

	void upgradePlanet();

	
	void setColor(sf::Color);
	
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getCenter()const;
	float getRadius()const;
	bool getActive()const;
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
	int getIndex()const;
	void resetUnits();
	void setUpgradeStage(UpgradeOptions stage, sf::Color color);
	UpgradeOptions getUpgrade(int stage);
	void setHealthStage();
	int getAmountToGenerate()const;


private:
	int m_index;
	int m_health = 100;
	int m_unitToUpgrade ;
	int m_counterToUpgrade = 0;
	int m_currentLevel;
	int m_amountOfUnits;
	int m_maxLevel;
	bool m_active = false;
	bool m_charged = false;
	bool m_attacked = false;
	sf::Color m_chargeColor;
	int m_counterToCharge = 0;
	sf::Text m_healthText;
	sf::Text m_chargeText;
	sf::IntRect m_upgRect;
	sf::IntRect m_healthRect;
	sf::Sprite m_healthBar;
	sf::Sprite m_upgrades;
	sf::Vector2f m_barScale;
	int m_AmountToGenerate;
};