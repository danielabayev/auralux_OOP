#pragma once
#include "ManagePlanet.h"

class ControlPlanet
{
public:
	ControlPlanet(sf::Color color);
	virtual ~ControlPlanet() = default;

	void addPlanet(ManagePlanet* mp);
	void resetData();
	void removePlanet(ManagePlanet* mp);
	bool checkIfBelongs(ManagePlanet*)const;

	sf::Color getColor()const;

protected:
	std::vector<ManagePlanet*> m_mp;
	sf::Color m_color;
};