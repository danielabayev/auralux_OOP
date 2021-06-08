#include "Planet.h"

Planet::Planet(sf::Color color, int maxLevel, sf::Vector2f pos)
	:Object(color), m_unitToUpgrade(30), m_currentLevel(1), m_maxLevel(maxLevel)
{
	// need to get position - the 300,300 position is for the check
	m_circle.setRadius(SMALLPLANET);
	//m_circle.setOrigin(30, 30);
	m_circle.setPosition(pos);
	m_circle.setOrigin(SMALLPLANET / 2, SMALLPLANET / 2);

	//the make of the units
	//sf::Vector2f center = m_circle.getOrigin();
	m_units.resize(1000);
	for (auto& unit : m_units)
		unit = std::make_shared<Unit>(sf::Color::Cyan, this);



	if (color != sf::Color::White)
	{
		for (size_t i = 0; i < START_UNIT_AMOUNT; i++)
			m_units[i]->setActive(true);
		m_amountOfUnits = START_UNIT_AMOUNT;
		m_active = true;
	}
	m_clock.restart();
}

void Planet::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);

	for (auto& unit : m_units)
		if (unit->getActive())
			unit->draw(window);
}

void Planet::move(Planet p)
{
	if (m_active)
	{
		generateUnits();
		for (auto& unit : m_units)
		{
			if (p.getCenter() == this->getCenter())
				unit->moveAround(this);
			if (p.getCenter() != this->getCenter())
				unit->defineTowards(&p);
		}
	}
}

void Planet::generateUnits()
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

void Planet::healPlanet()
{
	while (m_health != 100 && m_amountOfUnits != 0)
	{
		m_units[m_amountOfUnits - 1]->setActive(false);
		m_health++;
		m_amountOfUnits--;
	}
}

void Planet::addToUpgrade()
{
	while (m_counterToUpgrade < m_unitToUpgrade && m_amountOfUnits > 0 && m_currentLevel < 3)
	{
		m_units[m_amountOfUnits - 1]->setActive(false);
		m_counterToUpgrade++;
		m_amountOfUnits--;
	}
}

void Planet::upgradePlanet()
{
	int size;
	if (m_circle.getRadius() == SMALLPLANET)
		size = MEDIUMPLANET;
	else
		size = LARGEPLANET;
	m_circle.setRadius(size);
	m_circle.setOrigin(size / 2, size / 2);
	m_counterToUpgrade = 0;
	m_currentLevel++;
}

void Planet::setPosition(sf::Vector2f newPosition)
{
	m_circle.setPosition(newPosition);
}

sf::Vector2f Planet::getCenter()
{
	return m_circle.getOrigin() + m_circle.getPosition();
}

float Planet::getRadius()
{
	return m_circle.getRadius();
}
