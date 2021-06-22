#pragma once
#include "ManagePlanet.h"

class ControlPlanet
{
public:
	ControlPlanet(sf::Color color);
	~ControlPlanet() = default;

	void addPlanet(ManagePlanet* mp);
	void removePlanet(ManagePlanet* mp);
	void resetData();
	bool checkIfBelongs(ManagePlanet*)const;

	sf::Color getColor()const;

protected:
	std::vector<ManagePlanet*> m_mp;
	sf::Color m_color;
	
	
};