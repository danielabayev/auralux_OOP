#include "ControlPlanet.h"

ControlPlanet::ControlPlanet(sf::Color color) : m_color(color)
{

}

void ControlPlanet::addPlanet(std::shared_ptr<ManagePlanet> mp)
{
	m_mp.push_back(mp);
}

void ControlPlanet::removePlanet(std::shared_ptr<ManagePlanet> mp)
{
	auto it = m_mp.begin();
	while(it!= m_mp.end())
	{
		if (*it == mp)
		{
			it = m_mp.erase(it);
			break;
		}
		else
			it++;
			
	}
}

void ControlPlanet::resetData()
{
	if(m_mp.size() != 0)
		m_mp.clear();
}

sf::Color ControlPlanet::getColor() const
{
	return m_color;
}
