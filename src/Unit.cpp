#include "Unit.h"
#include <stdlib.h>
#include <time.h>
#include "Planet.h"
#include <cmath>
//class Planet;

Unit::Unit(sf::Color color, int kind, Planet* p) : Object(color,kind)
{
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

void Unit::move(Planet* p)
{
	if (targetPlanet.in_use)
		moveTowards();
	else
		moveAround(p);
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
	targetPlanet.in_use = true;
	targetPlanet.target.x = position.x;
	targetPlanet.target.y = position.y;
	if (targetPlanet.target.x - m_circle.getPosition().x == 0)
		if (targetPlanet.target.y - m_circle.getPosition().y > 0)
			targetPlanet.direction = DOWN;
		else 
			targetPlanet.direction = UP;
	else
	{
		targetPlanet.a = (targetPlanet.target.y - m_circle.getPosition().y) /
			(targetPlanet.target.x - m_circle.getPosition().x);
		targetPlanet.b = targetPlanet.target.y - (targetPlanet.target.x * targetPlanet.a);
		if (targetPlanet.target.x - m_circle.getPosition().x < 0)
			targetPlanet.direction = LEFT;
		else
			targetPlanet.direction = RIGHT;
	}

}

void Unit::moveTowards()
{
	sf::Vector2f position = m_circle.getPosition();
	switch (targetPlanet.direction)
	{
	case UP:
		//to check
	case DOWN:
		//to check
	case RIGHT:
		position.x += 0.5;
		//y = ax + b
		position.y = targetPlanet.a * position.x + targetPlanet.b;
		m_circle.setPosition(position);
		break;
	case LEFT:
		position.x -= 0.5;
		//y = ax + b
		position.y = targetPlanet.a * position.x + targetPlanet.b;
		m_circle.setPosition(position);
		break;
	default:
		break;
	}
	targetPlanet.in_use = checkDistance();
}

bool Unit::checkDistance()
{
	float distance = m_circle.getPosition().x - targetPlanet.target.x;
	if (distance < 0.3 && distance > -0.3)
	{
		m_circle.setPosition(targetPlanet.target);
		return false;
	}
	return true;
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