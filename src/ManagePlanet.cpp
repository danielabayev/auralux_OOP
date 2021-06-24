#include "ManagePlanet.h"

ManagePlanet::ManagePlanet(sf::Color color, int maxLevel, sf::Vector2f pos ,int index)
	:m_p(color,maxLevel,pos,index),m_amountToMove(0)
{
	m_units.resize(1000);
	for (auto& unit : m_units)
		unit = std::make_unique<Unit>(color, &m_p);
	if (color != sf::Color::White)
	{
		for (size_t i = 0; i < START_UNIT_AMOUNT; i++)
			m_units[i]->setActive(true);
		m_p.resetUnits();
		m_p.addUnits(START_UNIT_AMOUNT);
		m_p.setActive(true);
	}
	else
		m_p.resetUnits();
	m_clock.restart();
	m_neighbors.clear();
}

void ManagePlanet::draw(sf::RenderWindow& window)
{
	m_p.draw(window);
	if(m_p.getActive())
		for (int i = 0; i < m_p.getAmountOfUnits() ; i++)
			if (m_units[i]->getActive())
				m_units[i]->draw(window);
}

void ManagePlanet::move(ManagePlanet& mp , sf::Time timePassed)
{
	m_angle += 10;
	m_angle = int(m_angle) % 360;
	int unitsAround = m_around;
	m_around = 0;
	int angle = 360 / unitsAround;
	for (int i = 0; i < m_p.getAmountOfUnits(); i++)
	{
		if (m_p.getCenter() != mp.getPlanet().getCenter())///check if towards
			m_units[i]->defineTowards(mp.getPlanet());
		if (m_units[i]->move(mp.getPlanet() , timePassed , m_angle) != NOTCENTERD)
		{
			m_around++;
			//m_amountToMove++;
			//m_needToMove = true;
		}
		
	}
	if (m_around == 0)
		m_around++;
}



void ManagePlanet::healPlanet()
{
	while (m_p.getHealth() != MAX_HEALTH && m_p.getAmountOfUnits() != 0)
	{
		m_units[m_p.getAmountOfUnits() - 1]->setActive(false);
		m_p.setHealth(INC);
		m_p.decUnits();
	}
}

void ManagePlanet::arrangeUnits()
{
	std::vector<int> places;
	for (int i = m_p.getAmountOfUnits(); i > 0; i--)
	{
		if (!m_units[i]->getActive())
			places.push_back(i);
	}
	int size = places.size() - 1;
	while (places.size() != 0)
	{
		std::swap(m_units[places[size]], m_units[m_p.getAmountOfUnits()]);
		m_p.decUnits();
		places.pop_back();
		size--;
	}
}

void ManagePlanet::movePlayer(ManagePlanet& MP)
{
	if (MP.getPlanet().getCenter() == m_p.getCenter())
		if (m_p.getHealth() == MAX_HEALTH && m_p.isMaxUpgrade())
			return;
	
	for (int i = 0; i < m_p.getAmountOfUnits(); i++)
	{
		m_units[i]->defineTowards(MP.getPlanet());
		

	}
}


void ManagePlanet::generateUnits()
{
	if (m_p.getActive())
	{
		m_timePassed = m_clock.getElapsedTime();
		if (m_timePassed.asSeconds() > 6)
		{
			for (int i = m_p.getAmountOfUnits(); i < m_p.getAmountOfUnits() + 20; i++)
				m_units[i]->setActive(true);
			m_p.addUnits(20);
			m_clock.restart();
		}
	}
}

/*void ManagePlanet::determineAction()
{
	int activeUnits = m_amountOfUnits;
	if (m_p.getHealth() < MAX_HEALTH)
		healPlanet();
	else if (!m_p.isMaxUpgrade())
		addToUpgrade();
	
}*/

sf::Color ManagePlanet::getColor()
{
	return m_p.getColor();
}

Planet ManagePlanet::getPlanet() const
{
	return m_p;
}

void ManagePlanet::changePlanet(sf::Color newColor)
{
	//m_p.resetUnits();
	for (auto& unit : m_units)
	{
		unit->setColor(newColor);
		if (newColor == sf::Color::White)
		{
			unit->setActive(false);
		}
			
	}
		
}

bool ManagePlanet::getNeedToMove() const
{
	return m_needToMove;
}

void ManagePlanet::findCollisions(ManagePlanet& mp)
{
	int amount = m_p.getAmountOfUnits();
	
	for (int i = 0; i < m_p.getAmountOfUnits(); i++)
	{
		if (m_units[i]->inUse())
		{
			if (collide(mp.m_p, *m_units[i]) && m_units[i]->getTargetIndex() == mp.getPlanet().getIndex())
			{
				processCollision(mp.m_p, *m_units[i]);
				if (m_units[i]->getActive())
				{
					if (m_p.getIndex() != mp.getPlanet().getIndex())
					{
						
						mp.m_units[mp.getAmountOfUnits()]->setActive(true);
						mp.m_p.addUnits(1);
						
						m_units[i]->setActive(false);
						m_units[i].swap(m_units[m_p.getAmountOfUnits() - 1]);
						m_p.decUnits();
						
					}
				}
				else
				{
					m_units[i].swap(m_units[m_p.getAmountOfUnits() - 1]);
					m_p.decUnits();
				}
			}
			else
			{
				if (getColor() != mp.getColor() && mp.getPlanet().getActive())
				{
					for (int j = 0; j < mp.getAmountOfUnits(); j++)
					{
						if (collide(*m_units[i], *mp.m_units[j]))
						{
							processCollision(*m_units[i], *mp.m_units[j]);
							m_units[i].swap(m_units[m_p.getAmountOfUnits() - 1]);
							mp.m_units[j].swap(mp.m_units[mp.m_p.getAmountOfUnits() - 1]);
							m_p.decUnits();
							mp.m_p.decUnits();
						}
					}
				}
			}
		}
	}
}


void ManagePlanet::addNeighbor(ManagePlanet* neighbor)
{
	m_neighbors.push_back(neighbor);
}

int ManagePlanet::getAmountOfUnits() const
{
	return m_p.getAmountOfUnits();
}

std::vector<ManagePlanet*> ManagePlanet::getNeighbors() const
{
	return m_neighbors;
}

bool ManagePlanet::collide(const Object& object1, const Object& object2)
{
	return object1.getShape().getGlobalBounds().contains(object2.getShape().getPosition());
}
