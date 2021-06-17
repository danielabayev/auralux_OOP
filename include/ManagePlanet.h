#pragma once
#include "Planet.h"
#include "Unit.h"
#include "utillities.h"

class ManagePlanet
{
public:

	ManagePlanet(sf::Color color, int maxLevel, sf::Vector2f pos);
	~ManagePlanet() = default;
	virtual void draw(sf::RenderWindow& window);
	void move(ManagePlanet& MP);
	void moveOwnerships(const std::vector<std::unique_ptr<ManagePlanet>>& planets);
	void healPlanet();
	void addToUpgrade();
	void upgradePlanet();
	void charge(sf::Color);
	void generateUnits();
	void determineAction();
	sf::Color getColor();
	Planet getPlanet()const;
	bool getNeedToMove()const;
	void underAttack();

private:
	sf::Clock m_clock;
	sf::Time m_timePassed;
	Planet m_p;
	int m_amountOfUnits;
	std::vector<std::unique_ptr<Unit>> m_units; //unique_ptr
	bool m_needToMove = false;
	int m_amountToMove;
	sf::Color m_chargeColor = sf::Color::White;
	int m_counterToCharge = 0;
	bool upgraded = false;
	
};