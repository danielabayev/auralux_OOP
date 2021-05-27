#pragma once
#include <SFML/Graphics.hpp>

const sf::Vector2f KB_UP = { 0,-1 };
const sf::Vector2f KB_DOWN = { 0,1 };
const sf::Vector2f KB_LEFT = { -1,0 };
const sf::Vector2f KB_RIGHT = { 1,0 };
const sf::Vector2f KB_STAY = { 0,0 };
const sf::Vector2f TO_DELETED = { -1,-1 };

const int OBJECTS = 14;
const int COMPARISON = 30;

const int NUMBER_OF_PRESENT = 4;

const int PRESENT = 0;
const int ENEMY = 1;
const int LADDER = 2;
const int COIN = 3;
const int FLOOR = 4;
const int ROD = 5;
const int BACKGROUND = 6;
const int STARTBACKGROUND = 7;
const int STARTBUTTON = 8;
const int ENDBUTTON = 9;
const int LIVE = 10;
const int SCORE = 11;
const int PLAYER = 12;
const int TIMER = 13;
const int LIVEFONT = 0;
const int SCOREFONT = 1;
const int TIMEFONT = 2;
