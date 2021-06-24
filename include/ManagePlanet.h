#pragma once
#include "Planet.h"
#include "Unit.h"
#include "utillities.h"
#include "CollisionHandling.h"

class ManagePlanet
{
public:

	ManagePlanet(sf::Color color, int maxLevel, sf::Vector2f pos , int index);
	~ManagePlanet() = default;
	virtual void draw(sf::RenderWindow& window);
	void move(ManagePlanet& MP , sf::Time timePassed);
	void moveOwnerships(const std::vector<std::unique_ptr<ManagePlanet>>& planets);
	void healPlanet();
	void arrangeUnits();
	void movePlayer(ManagePlanet& MP);
	void generateUnits();
	void determineAction();
	sf::Color getColor();
	Planet getPlanet()const;
	void changePlanet(sf::Color);
	bool getNeedToMove()const;
	void findCollisions(ManagePlanet& mp);
	void addNeighbor(ManagePlanet *neighbor);
	int getAmountOfUnits()const;
	std::vector<ManagePlanet*> getNeighbors()const;
	bool collide(const Object& object1, const Object& object2);
	

private:
	sf::Clock m_clock;
	sf::Time m_timePassed;
	Planet m_p;
	std::vector<ManagePlanet*> m_neighbors;
	std::vector<std::unique_ptr<Unit>> m_units;
	bool m_needToMove = false;
	int m_amountToMove;
	bool upgraded = false;
	int m_angle;
	int m_around = 1;
	
};