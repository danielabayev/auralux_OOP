#include "Unit.h"
#include <stdlib.h>
#include <time.h>
#include "Planet.h"
#include <cmath>

Unit::Unit(sf::Color color, Planet* p) : Object(color)
{
	m_circle.setRadius(2);
	m_circle.setTexture(&Graphic::PicturesObject().getParticleTexture(findColor(color)));
	m_angle = rand() % 360;
	sf::Vector2f position = calculateNewPosition(*p);
	m_circle.setPosition(position);
	m_clock.restart();
}

sf::Vector2f Unit::calculateNewPosition(const Planet& p)
{
	sf::Vector2f position;
	float inRadian = PI * m_angle / 180;
	sf::Vector2f centerOfPlanet = p.getCenter();
	float radius = p.getRadius();
	position.x = p.getCenter().x + (radius * 1.4 * std::cos(inRadian));
	position.y = p.getCenter().y + (radius * 1.4 * std::sin(inRadian));
	return position;
}

sf::Vector2f Unit::move(const Planet& p,const sf::Time& timePassed , int angle)
{
	if (m_targetPlanet.in_use)
		return moveTowards(timePassed);
	else
		moveAround(p, timePassed, angle);			
	return NOTCENTERD;
}

void Unit::moveAround(const Planet& p,const sf::Time& timePassed , int angle)
{
	float diff = m_angle - angle;
	m_angle += (diff/10) * timePassed.asSeconds();
	m_angle = int(m_angle) % 360;
	sf::Vector2f position = calculateNewPosition(p);
	m_circle.setPosition(position);
}

void Unit::defineTowards(const Planet& p)
{
	if (m_targetPlanet.in_use)
		return;
	sf::Vector2f position = p.getCenter();
	m_targetPlanet.in_use = true;
	m_targetPlanet.targetIndex = p.getIndex();
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

sf::Vector2f Unit::moveTowards(const sf::Time& timePassed)
{
	sf::Vector2f position = m_circle.getPosition();
	switch (m_targetPlanet.direction)
	{
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

void Unit::setColor(const sf::Color& newColor)
{
	m_circle.setTexture(&Graphic::PicturesObject().getParticleTexture(findColor(newColor)));
	m_color = newColor;
}

void Unit::setActive(bool Active)
{
	m_active = Active;
	if (Active)
		m_targetPlanet.in_use = false;
}

void Unit::setWaitToMove(bool moved)
{
	m_waitToMove = moved;
}

bool Unit::getWaitToMove()const
{
	return m_waitToMove;
}

int Unit::getTargetIndex() const
{
	return m_targetPlanet.targetIndex;
}

sf::Vector2f Unit::getTargetPlanet()const
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
