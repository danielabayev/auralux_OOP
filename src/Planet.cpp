#include "Planet.h"

Planet::Planet(sf::Color color, int maxLevel, sf::Vector2f pos)
	:Object(color), m_unitToUpgrade(30), m_currentLevel(1), m_maxLevel(maxLevel)
{
	m_circle.setRadius(SMALLPLANET);
	m_circle.setPosition(pos);
	m_circle.setOrigin(SMALLPLANET / 2, SMALLPLANET / 2);

	m_statusBar.setPosition(pos.x - 18, pos.y + 60);
	m_statusBar.setFillColor(sf::Color::Transparent);
	m_statusBar.setOutlineColor(sf::Color::Transparent);
	m_statusBar.setOutlineThickness(1);
	sf::Vector2f test(60, 7);
	m_statusBar.setSize(test);
	m_fillBarSize = sf::Vector2f(0, 7);
	m_fillBar.setPosition(pos.x - 16, pos.y + 60);
	m_fillBar.setFillColor(sf::Color::Transparent);
	m_fillBar.setSize(m_fillBarSize);
	m_chargeColor = sf::Color::White;
	

	int pcolor = findColor(color);
	m_circle.setTexture(&Graphic::PicturesObject().getPlanet(pcolor));
	
	/*m_font = Graphic::PicturesObject().getFont();
	m_healthText.setFont(m_font);
	m_healthText.setFillColor(sf::Color::Red);
	m_healthText.setCharacterSize(20);
	m_healthText.setScale(1, 1);
	m_chargeText.setFont(m_font);
	m_healthText.setFillColor(sf::Color::Black);
	m_chargeText.setFillColor(sf::Color::Black);
	m_healthText.setPosition(pos.x - 18, pos.y + 60);
	m_chargeText.setPosition(pos.x - 50, pos.y + 60);*/

}

void Planet::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
	//window.draw(m_statusBar);
	//window.draw(m_fillBar);
	/*std::string hp = std::to_string(m_health);
	m_healthText.setString(hp);
	if(m_color == sf::Color::White)
		std::string st = "C" + std::to_string(m_counterToCharge);
	else
		std::string st = "U" + std::to_string(m_counterToUpgrade);
	window.draw(m_healthText);
	window.draw(m_chargeText)*/;
}



void Planet::setColor(sf::Color newColor)
{
	m_color = newColor;
	m_circle.setTexture(&Graphic::PicturesObject().getPlanet(findColor(newColor)));
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
	m_currentLevel++;
	m_counterToUpgrade = 0;
	sf::Vector2f newpos(m_statusBar.getPosition().x +(size / 4), m_statusBar.getPosition().y + (size / 2));
	m_statusBar.setPosition(newpos);
	m_fillBar.setPosition(newpos);

}

void Planet::setPosition(sf::Vector2f newPosition)
{
	m_circle.setPosition(newPosition);
}

sf::Vector2f Planet::getCenter()const
{
	return m_circle.getOrigin() + m_circle.getPosition();
}

float Planet::getRadius()const
{
	return m_circle.getRadius();
}

bool Planet::getActive() const
{
	return m_active;
}

int Planet::findColor(sf::Color color)
{
	if (color == sf::Color::Blue)
		return BLUEP;
	else if (color == sf::Color::Red)
		return REDP;
	else if (color == sf::Color::Yellow)
		return YELLOWP;
	else if (color == sf::Color::Green)
		return GREENP;
	else
		return GREYP;
	
}

void Planet::setActive(bool Active)
{
	m_active = Active;
}

int Planet::getHealth() const
{
	return m_health;
}

void Planet::setHealth(HealthAction action)
{
	if (action == INC)
		m_health++;
	else
	{
		m_health--;
	}

	if (m_health < 100)
	{
		m_statusBar.setOutlineColor(sf::Color::White);
		m_fillBar.setFillColor(m_color);

		if (m_health > 80)
		{
			m_fillBarSize.x = (m_health * 0.6);
			m_fillBar.setSize(m_fillBarSize);
		}
		else
		{
			m_fillBarSize.x = (m_health / 2);
			m_fillBar.setSize(m_fillBarSize);
		}
	}

	if (m_health == 0 || m_health == MAX_HEALTH)
	{
		m_statusBar.setOutlineColor(sf::Color::Transparent);
		m_fillBar.setFillColor(sf::Color::Transparent);
		m_fillBarSize.x = 0;
		m_fillBar.setSize(m_fillBarSize);
	}
	
		
}

int Planet::getCounterToUpgrade() const
{
	return m_counterToUpgrade;
}

void Planet::setCounterToUpgrade()
{
	m_counterToUpgrade++;
}

void Planet::setFillBar(HealthAction action , sf::Color color)
{
	if (action == INC)
	{
		m_statusBar.setOutlineColor(color);
		if (m_fillBar.getFillColor() == sf::Color::Transparent)
		{
			m_fillBar.setFillColor(color);
		}
		m_fillBarSize.x += 10;
		m_fillBar.setSize(m_fillBarSize);
		if (m_fillBarSize.x == m_statusBar.getSize().x)
		{
			m_fillBarSize.x = 0;
			m_fillBar.setFillColor(sf::Color::Transparent);
			m_statusBar.setOutlineColor(sf::Color::Transparent);
		}
	}
	else
	{
		m_fillBarSize.x -= 10;
		m_fillBar.setSize(m_fillBarSize);
		if(m_fillBarSize.x == 0)
			m_fillBar.setFillColor(sf::Color::Transparent);
	}

}

int Planet::getAmountToUpgrade() const
{
	return m_unitToUpgrade;
}

bool Planet::isMaxUpgrade() const
{
	return m_currentLevel == m_maxLevel;
}

void Planet::charge(sf::Color newCharger)
{
	if (m_chargeColor == sf::Color::White)
		m_chargeColor = newCharger;

	if (newCharger == m_chargeColor)
	{
		m_counterToCharge++;
		if (m_counterToCharge % 5 == 0)
		{
			setFillBar(INC, newCharger);
		}
	}
	else
	{
		if (m_counterToCharge != 0)
		{
			m_counterToCharge--;
			if (m_counterToCharge % 5 == 0)
			{
				setFillBar(DEC, newCharger);
			}
		}
		else
		{
			m_chargeColor = newCharger;
			m_counterToCharge++;
			if (m_counterToCharge % 5 == 0)
			{
				setFillBar(INC, newCharger);
			}
		}
	}
	

	if (m_counterToCharge == m_unitToUpgrade)
	{
		setColor(m_chargeColor);
		setActive(true);
		m_counterToCharge = 0;
		//for (auto& unit : m_units)
			//unit->setColor(m_chargeColor);
		//m_amountOfUnits = 0;
	}
}

void Planet::underAttack()
{
	setHealth(DEC);

	if (m_health == 0)
	{
		setActive(false);
		setColor(sf::Color::White);
		m_health = MAX_HEALTH;
		m_currentLevel = 1;
		m_counterToUpgrade = 0;
		m_counterToCharge = 0;
		m_amountOfUnits = 0;
		m_chargeColor = sf::Color::White;
		if (m_circle.getRadius() != SMALLPLANET)
		{
			m_circle.setRadius(SMALLPLANET);
			m_circle.setOrigin(SMALLPLANET / 2, SMALLPLANET / 2);
		}	
	}
}

void Planet::addToUpgrade()
{
	if(m_counterToUpgrade < m_unitToUpgrade)
	{
		m_counterToUpgrade++;
		if (m_counterToUpgrade % 5 == 0)
			setFillBar(INC, getColor());
		if (m_counterToUpgrade == m_unitToUpgrade)
			upgradePlanet();
	}
}

int Planet::getAmountOfUnits() const
{
	return m_amountOfUnits;
}

void Planet::addUnits(int i)
{
	m_amountOfUnits += i;
}

void Planet::decUnits()
{
	if (m_amountOfUnits != 0)
		m_amountOfUnits--;
	else
		throw "zero units";

}

void Planet::resetUnits()
{
	m_amountOfUnits = 0;
}
