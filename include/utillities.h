#pragma once
#include <SFML/Graphics.hpp>
#include <utility>

const int OPTIONS = 6;
const int HEAL = 0;
const int REINFORCMENT_TO = 1;
const int CONQUER_NEW = 2;
const int UPGRADE = 3;
const int CONQUER_CONQUER = 4;
const int REINFORCMENT_FROM = 5;

const int TEXTURES = 2;
const int STARTBACKGROUND = 0;
const int RIGHTARROW = 1;

const int STARTWIDTH = 800;
const int STARTHEIGHT = 800;
const int GAMEWIDTH = 1000;
const int GAMEHEIGHT = 900;

const int MAX_OWNERS = 5;
const int PLAYER_OWN = 0;

const int START_UNIT_AMOUNT = 30;
const float PI = float(3.14159265358979323846);

const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;

const int OPPONENTS = 4;
enum HealthAction
{
	INC, DEC
};

enum class MenuOptions : int
{//the menu screen choine enum
	START = 2, LEVEL = 4, INSTRUCTIONS = 6, EXIT = 8
};

enum class UpgradeOptions : int
{//the menu screen choine enum
	ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, NONE = 6
};

enum class LevelOptions : int
{//the menu screen choine enum
	MENU = 2, ONE = 3, TWO = 4, THREE = 5, FOUR = 6, FIVE = 7, SIX = 8, SEVEN = 9
};

enum ParColor_t
{
	BLUE1, RED1, YELLOW1 , GREEN1
};

enum PlanetColor_t
{
	BLUE_BIG, YELLOW_BIG, RED_BIG, GREEN_BIG , EMPTY
};

enum Planets
{
	BLUEP , REDP , YELLOWP , GREENP, GREYP
};
enum Opponents
{
	RED , YELLOW , GREEN , CYAN
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
	int targetIndex;
};