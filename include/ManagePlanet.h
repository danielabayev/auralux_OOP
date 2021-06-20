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
	void charge(sf::Color);
	void generateUnits();
	void determineAction();
	sf::Color getColor();
	Planet getPlanet()const;
	bool getNeedToMove()const;
	void underAttack();
	void addNeighbor(ManagePlanet *neighbor);
	int getAmountOfUnits()const;
	std::vector<ManagePlanet*> getNeighbors()const;

private:
	sf::Clock m_clock;
	sf::Time m_timePassed;
	Planet m_p;
	std::vector<ManagePlanet*> m_neighbors;
	int m_amountOfUnits;
	std::vector<std::unique_ptr<Unit>> m_units;
	bool m_needToMove = false;
	int m_amountToMove;
	sf::Color m_chargeColor = sf::Color::White;
	int m_counterToCharge = 0;
	bool upgraded = false;
	
};