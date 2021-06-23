#include "Unit.h"
#include <stdlib.h>
#include <time.h>
#include "Planet.h"
#include <cmath>

Unit::Unit(sf::Color color, Planet* p) : Object(color)
{
	m_circle.setRadius(2);
	m_circle.setFillColor(color);
	m_angle = rand() % 360;
	sf::Vector2f position = calculateNewPosition(*p);
	m_circle.setPosition(position);
	m_clock.restart();
}

sf::Vector2f Unit::calculateNewPosition(Planet p)
{
	sf::Vector2f position;
	float inRadian = PI * m_angle / 180;
	sf::Vector2f centerOfPlanet = p.getCenter();
	float radius = p.getRadius();
	position.x = p.getCenter().x + (radius * 1.4 * std::cos(inRadian));
	position.y = p.getCenter().y + (radius * 1.4 * std::sin(inRadian));
	return position;
}

sf::Vector2f Unit::move(Planet p , sf::Time timePassed)
{
	if (m_targetPlanet.in_use)
		return moveTowards(timePassed);
	else
	{
			moveAround(p , timePassed);
			//m_clock.restart();
				
	}
	return NOTCENTERD;
}

void Unit::moveAround(Planet p , sf::Time timePassed)
{
	m_angle += 10 * timePassed.asSeconds();
	sf::Vector2f position = calculateNewPosition(p);
	m_circle.setPosition(position);
}

void Unit::defineTowards(Planet p)
{//check UP and DOWN
	if (m_targetPlanet.in_use)
		return;
	sf::Vector2f position = p.getCenter();
	m_targetPlanet.in_use = true;
	m_targetPlanet.target.x = position.x;
	m_targetPlanet.target.y = position.y;
	m_targetPlanet.targetCenter = p.getCenter();

	if (m_targetPlanet.target.x - m_circle.getPosition().x == 0)
		if (m_targetPlanet.target.y - m_circle.getPosition().y > 0)
			m_targetPlanet.direction = DOWN;
		else 
			m_targetPlanet.direction = UP;
	else
	{
		m_targetPlanet.a = (m_targetPlanet.target.y - m_circle.getPosition().y) /
			(m_targetPlanet.target.x - m_circle.getPosition().x);
		m_targetPlanet.b = m_targetPlanet.target.y - (m_targetPlanet.target.x * m_targetPlanet.a);
		if (m_targetPlanet.target.x - m_circle.getPosition().x < 0)
			m_targetPlanet.direction = LEFT;
		else
			m_targetPlanet.direction = RIGHT;
	}

}

sf::Vector2f Unit::moveTowards(sf::Time timePassed)
{
	sf::Vector2f position = m_circle.getPosition();
	switch (m_targetPlanet.direction)
	{
	case UP:
		//to check
	case DOWN:
		//to check
	case RIGHT:
		position.x += 0.5 * timePassed.asSeconds();
		//y = ax + b
		position.y = m_targetPlanet.a * position.x + m_targetPlanet.b;
		m_circle.setPosition(position);
		break;
	case LEFT:
		position.x -= 0.5 * timePassed.asSeconds();
		//y = ax + b
		position.y = m_targetPlanet.a * position.x + m_targetPlanet.b;
		m_circle.setPosition(position);
		break;
	default:
		break;
	}
	m_targetPlanet.in_use = checkDistance();
	if (m_targetPlanet.in_use)
		return NOTCENTERD;
	else
		return m_targetPlanet.targetCenter;
}

bool Unit::checkDistance()
{
	float distance = m_circle.getPosition().x - m_targetPlanet.target.x;
	if (distance < 0.3 && distance > -0.3)
	{
		m_circle.setPosition(m_targetPlanet.target);
		//m_waitToMove = true;
		return false;
	}
	return true;
}

void Unit::handleCollision(Planet* p)
{//back the x and y to previos position then


}

void Unit::setColor(sf::Color newColor)
{
	m_circle.setFillColor(newColor);
	m_color = newColor;
}

void Unit::setActive(bool Active)
{
	m_active = Active;
	if (Active)
	{
		m_targetPlanet.in_use = false;
		m_otherWay.in_use = false;
	}
}

void Unit::setWaitToMove(bool moved)
{
	m_waitToMove = moved;
}

bool Unit::getWaitToMove()const
{
	return m_waitToMove;
}

sf::Vector2f Unit::getTargetPlanet()
{
	return m_targetPlanet.targetCenter;
}

void Unit::defineTowards()
{
	sf::Vector2f curentPosition = m_circle.getPosition();
	sf::Vector2f targetPosition = m_targetPlanet.target;

}
bool Unit::inUse()const
{
	return m_targetPlanet.in_use;
}

void Unit::setInUse(bool used)
{
	m_targetPlanet.in_use = used;
}
