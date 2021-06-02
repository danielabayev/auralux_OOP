#include "Unit.h"
#include <stdlib.h>
#include <time.h>
#include "Planet.h"
#include <cmath>
//class Planet;

Unit::Unit(sf::Color color, int kind, Planet* p) : Object(color,kind)
{
	//temp->target_x = s->x + radius * cos(theta + 2 * PI * i / s->curr_level);
	//temp->target_y = s->y + radius * sin(theta + 2 * PI * i / s->curr_level);
	
	sf::Vector2f position;

	m_angle = rand() % 360;
	float inRadian = PI * m_angle / 180;
	sf::Vector2f centerOfPlanet = p->getCenter();
	float radius = p->getRadius();
	position.x = p->getCenter().x + (radius * 1.1 * std::cos(inRadian));
	position.y = p->getCenter().y + (radius * 1.1 * std::sin(inRadian));

	m_circle.setPosition(position);
}

void Unit::move(Planet* p)
{
	sf::Vector2f position;
	m_angle += 10;
	float inRadian = PI * m_angle / 180;
	sf::Vector2f centerOfPlanet = p->getCenter();
	float radius = p->getRadius();
	position.x = p->getCenter().x + (radius * 1.1 * std::cos(inRadian));
	position.y = p->getCenter().y + (radius * 1.1 * std::sin(inRadian));
	m_circle.setPosition(position);
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