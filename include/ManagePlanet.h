#pragma once
#include "Planet.h"
#include "Unit.h"
#include "utillities.h"
#include "CollisionHandling.h"

class ManagePlanet
{
public:

	ManagePlanet(const sf::Color& color, int maxLevel,const sf::Vector2f& pos , int index);
	~ManagePlanet() = default;
	//the game loop funcs
	virtual void draw(sf::RenderWindow& window);
	void move(const ManagePlanet& MP ,const sf::Time& timePassed);
	void arrangeUnits();
	void generateUnits();
	
	//gets sets
	sf::Color getColor()const;
	Planet getPlanet()const;
	bool getNeedToMove()const;
	void addNeighbor(ManagePlanet *neighbor);
	int getAmountOfUnits()const;
	
	//needs funcs
	void movePlayer(const ManagePlanet& MP);
	void changePlanet(const sf::Color&);
	std::vector<ManagePlanet*> getNeighbors()const;
	void findCollisions(ManagePlanet& mp);

private:
	sf::Clock m_clock;
	sf::Time m_timePassed;
	Planet m_p;
	std::vector<ManagePlanet*> m_neighbors;
	std::vector<std::unique_ptr<Unit>> m_units;
	
	//for the planet data
	bool m_needToMove = false;
	int m_amountToMove;
	bool upgraded = false;
	
	//for the unit serrounding
	int m_angle;
	int m_around = 1;
	

	//private funcs:
	bool collide(const Object& object1, const Object& object2)const;
	void healPlanet();
};