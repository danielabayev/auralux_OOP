#pragma once
#include "ManagePlanet.h"

class ControlPlanet
{
public:
	ControlPlanet(sf::Color color);
	~ControlPlanet() = default;

	void addPlanet(std::shared_ptr<ManagePlanet> mp);
	void removePlanet(std::shared_ptr<ManagePlanet> mp);
	void resetData();

	void doAction();

	sf::Color getColor()const;
	//void upgradePlanet();
	//void move units
	//heal planet

private:

	std::vector<std::shared_ptr<ManagePlanet>> m_mp;
	sf::Color m_color;
	
	
};