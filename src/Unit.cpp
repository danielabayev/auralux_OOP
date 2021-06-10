#include "Unit.h"
#include <stdlib.h>
#include <time.h>
#include "Planet.h"
#include <cmath>
//class Planet;

Unit::Unit(sf::Color color, Planet* p) : Object(color)
{
	m_circle.setRadius(2);
	m_angle = rand() % 360;
	sf::Vector2f position = calculateNewPosition(p);
	m_circle.setPosition(position);
}

sf::Vector2f Unit::calculateNewPosition(Planet* p)
{
	sf::Vector2f position;
	float inRadian = PI * m_angle / 180;
	sf::Vector2f centerOfPlanet = p->getCenter();
	float radius = p->getRadius();
	position.x = p->getCenter().x + (radius * 1.1 * std::cos(inRadian));
	position.y = p->getCenter().y + (radius * 1.1 * std::sin(inRadian));
	return position;
}

sf::Vector2f Unit::move(Planet* p)
{
	if (m_targetPlanet.in_use)
		return moveTowards();
	else
		moveAround(p);
	return NOTCENTERD;
}

void Unit::moveAround(Planet* p)
{
	m_angle += 10;
	sf::Vector2f position = calculateNewPosition(p);
	m_circle.setPosition(position);
}

void Unit::defineTowards(Planet* p)
{//check UP and DOWN
	sf::Vector2f position = calculateNewPosition(p);
	m_targetPlanet.in_use = true;
	m_targetPlanet.target.x = position.x;
	m_targetPlanet.target.y = position.y;
	m_targetPlanet.targetCenter = p->getCenter();

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

sf::Vector2f Unit::moveTowards()
{
	sf::Vector2f position = m_circle.getPosition();
	switch (m_targetPlanet.direction)
	{
	case UP:
		//to check
	case DOWN:
		//to check
	case RIGHT:
		position.x += 0.5;
		//y = ax + b
		position.y = m_targetPlanet.a * position.x + m_targetPlanet.b;
		m_circle.setPosition(position);
		break;
	case LEFT:
		position.x -= 0.5;
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
		m_waitToMove = true;
		return false;
	}
	return true;
}

void Unit::handleCollision(Planet* p)
{//back the x and y to previos position then 

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

/*void generate_dots(Unit* s) {
	int dots_per_cycle = s->curr_level;
	int i = 0;
	int radius = ANNULUS_INNER_RADIUS + my_random() % (int)(ANNULUS_OUTER_RADIUS - ANNULUS_INNER_RADIUS);
	int angle = my_random() % 360;
	float theta = RADIAN(angle);//pi * angel / 180
	dot* temp;

	while (dots_per_cycle) { /* gray suns have curr_level zero, so loop won't execute */
	/*	if (s->health < HEALTH_MAX) { /* injured sun will prefer healing itself before generating dots */
/*			s->health++;
			dots_per_cycle--;
			continue;
		}
		temp = (dot*)malloc(sizeof(dot));
		no_of_dots[s->color / 2]++;
		if (!temp) {
			perror("generate dots : temp");
		}
		temp->color = s->color;
		temp->active = 1;
		temp->reached_sun = 1; /* already near the parent sun */
/*		temp->x = s->x;
		temp->y = s->y;
		temp->target_sun = s;
		temp->target_dot = NULL;
		temp->move_dot = move_dot;
		temp->target_x = s->x + radius * cos(theta + 2 * PI * i / s->curr_level);
		temp->target_y = s->y + radius * sin(theta + 2 * PI * i / s->curr_level);
		i++;
		temp->next = dot_ptr_grid[s -
	}
}*/