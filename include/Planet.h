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
	// c/d-tor
	Planet(const sf::Color& color, int maxLevel, const sf::Vector2f& pos , int index);
	~Planet() = default;

	virtual void draw(sf::RenderWindow& window)const;
	void upgradePlanet();

	//gets and sets
	void setColor(const sf::Color& newColor);
	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getCenter()const;
	float getRadius()const;
	bool getActive()const;
	void setActive(bool Active);
	int getHealth()const;
	void setHealth(const HealthAction& action);
	int getCounterToUpgrade()const;
	void setCounterToUpgrade();
	int getAmountToUpgrade()const;
	int getAmountOfUnits()const;

	//funcs of the planet
	bool isMaxUpgrade()const;
	void charge(const sf::Color&);
	void underAttack();
	void addToUpgrade();
	void addUnits(int i);
	void decUnits();
	int getIndex()const;
	void resetUnits();
	void setUpgradeStage(const UpgradeOptions& stage,const sf::Color& color);
	UpgradeOptions getUpgrade(int stage)const;
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