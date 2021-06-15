#include "ManagePlanet.h"

ManagePlanet::ManagePlanet(sf::Color color, int maxLevel, sf::Vector2f pos)
	:m_p(color,maxLevel,pos),m_amountToMove(0)
{
	m_units.resize(1000);
	for (auto& unit : m_units)
		unit = std::make_shared<Unit>(sf::Color::Cyan, &m_p);
	if (color != sf::Color::White)
	{
		for (size_t i = 0; i < START_UNIT_AMOUNT; i++)
			m_units[i]->setActive(true);
		m_amountOfUnits = START_UNIT_AMOUNT;
		m_p.setActive(true);
	}
	m_clock.restart();
}

void ManagePlanet::draw(sf::RenderWindow& window)
{
	m_p.draw(window);
	for (auto& unit : m_units)
		if (unit->getActive())
			unit->draw(window);
}

void ManagePlanet::move(ManagePlanet mp)
{
	Planet* p;
	if (m_p.getActive())
	{
		for (int i = 0; i < m_amountOfUnits; i++)
	{
			//if (p.getCenter() == this->getCenter())
				//unit->moveAround(this);
			if (m_p.getCenter() != mp.getPlanet().getCenter())///check if towards
				m_units[i]->defineTowards(&mp.getPlanet());

			if (m_units[i]->move(&mp.getPlanet()) != NOTCENTERD)
		{
				m_amountToMove++;
				m_needToMove = true;
			}
		}
	}
}

void ManagePlanet::moveOwnerships(std::vector<std::shared_ptr<ManagePlanet>> planets)
{
	sf::Vector2f targetPosition;
	int amountOfUnit = m_amountOfUnits;
	for (int i = 0; i < amountOfUnit && m_needToMove; i++)
		if (m_units[i]->getWaitToMove())
		{
			targetPosition = m_units[i]->getTargetPlanet();
			for (auto& mp : planets)
				if (targetPosition == mp->getPlanet().getCenter())
				{
					m_units[i]->setWaitToMove(false);
					mp->m_units.insert(mp->m_units.begin(), m_units[i]);
					mp->m_amountOfUnits++;
					m_units.erase(m_units.begin()+i);
					m_amountOfUnits--;
					m_amountToMove--;
					if (m_amountToMove == 0)
						m_needToMove = false;
				}
		}
}

void ManagePlanet::generateUnits()
{
	if (m_p.getActive())
	{
		m_timePassed = m_clock.getElapsedTime();
		if (m_timePassed.asSeconds() > 4)
		{
			for (int i = m_amountOfUnits; i < m_amountOfUnits + 10; i++)
				m_units[i]->setActive(true);
			m_amountOfUnits += 10;
			m_clock.restart();
		}
	}
}

sf::Color ManagePlanet::getColor()
{
	return m_p.getColor();
}

Planet ManagePlanet::getPlanet() const
{
	return m_p;
}

bool ManagePlanet::getNeedToMove() const
{
	return m_needToMove;
}
