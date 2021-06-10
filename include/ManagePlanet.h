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
	void move(ManagePlanet MP);
	void moveOwnerships(std::vector<std::shared_ptr<ManagePlanet>> planets);
	void generateUnits();

	Planet getPlanet()const;
	bool getNeedToMove()const;

private:
	sf::Clock m_clock;
	sf::Time m_timePassed;
	Planet m_p;
	int m_amountOfUnits;
	std::vector<std::shared_ptr<Unit>> m_units; //unique_ptr
	bool m_needToMove = false;
	int m_amountToMove;
	
};