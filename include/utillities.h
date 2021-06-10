#pragma once
#include <SFML/Graphics.hpp>
#include <utility>


/*const sf::Vector2f KB_UP = { 0,-1 };
const sf::Vector2f KB_DOWN = { 0,1 };
const sf::Vector2f KB_LEFT = { -1,0 };
const sf::Vector2f KB_RIGHT = { 1,0 };
const sf::Vector2f KB_STAY = { 0,0 };
const sf::Vector2f TO_DELETED = { -1,-1 };*/
const int MAX_OWNERS = 5;
const int PLAYER_OWN = 0;
const int FIRST_COMPUTER_OWN = 1;
const int SECONED_COMPUTER_OWN = 2;
const int NO_OWN = 3;
const int VELOCITY = 30;
const int PLANET = 0;
const int UNIT = 1;
const int START_UNIT_AMOUNT = 30;
const float PI = 3.14159265358979323846;

const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;

const sf::Vector2f NOTCENTERD(-1, -1);

enum PlanetColor_t
{
	BLUE_BIG, YELLOW_BIG, RED_BIG, EMPTY
};

enum class PlanetType : char
{
	player = 'B', green = 'G', orange = 'O', empty = 'E'
};



struct line
{//struct to find the line between the two planets, in use only when the unit move to new planet
	bool in_use = false;
	float a;
	float b;
	sf::Vector2f target;
	int direction;
	sf::Vector2f targetCenter;
};

struct parabola
{//struct to find the parabola after the collision beetwen the unit and the planet
	bool in_use = false;
	float a;
	float b;
	float c;
	sf::Vector2f target;
	int direction;
};
