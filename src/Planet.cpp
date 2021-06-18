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

	int pcolor = findColor(color);
	m_circle.setTexture(&Graphic::PicturesObject().getPlanet(pcolor));
	

}

void Planet::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
	window.draw(m_statusBar);
	window.draw(m_fillBar);

}

sf::Color Planet::getColor()
{
	return m_color;
}

void Planet::setColor(sf::Color newColor)
{
	m_color = newColor;
	m_circle.setTexture(&Graphic::PicturesObject().getPlanet(findColor(newColor)));
}

sf::CircleShape Planet::getShape() const
{
	return m_circle;
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
		m_statusBar.setOutlineColor(sf::Color::White);
		if (m_fillBar.getFillColor() == sf::Color::Transparent)
			m_fillBar.setFillColor(color);
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
