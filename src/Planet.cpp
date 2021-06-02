#include "Planet.h"

Planet::Planet(sf::Color color, int kind,int maxLevel) 
	:Object(color,kind),m_unitToUpgrade(30),m_currentLevel(1),m_maxLevel(maxLevel)
{
	//m_circle.setOrigin(30, 30);
	m_circle.setPosition(300, 300);
	m_circle.setOrigin(30, 30);

	//the make of the units
	//sf::Vector2f center = m_circle.getOrigin();
	m_units.resize(1000);
	for (auto &unit : m_units)
		unit = std::make_shared<Unit>(sf::Color::Cyan,UNIT,this);
	
	//the active units
	for (size_t i = 0; i < START_UNIT_AMOUNT; i++)
		m_units[i]->setActive(true);
}

void Planet::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
	for (auto& unit : m_units)
		if (unit->getActive())
			unit->draw(window);
}

void Planet::move()
{
	for (auto& unit : m_units)
	{
		unit->move(this);
	}
}

void Planet::generateUnits()
{
	int toGenerate = rand()%10;
	while (toGenerate > 0)
	{

	}
}

sf::Vector2f Planet::getCenter()
{
	return m_circle.getOrigin() + m_circle.getPosition();
}

float Planet::getRadius()
{
	return m_circle.getRadius();
}
