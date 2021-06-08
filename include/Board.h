#pragma once

#include "Planet.h"
#include "Graphic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::stringstream;
using std::ifstream;
using std::vector;
using std::string;
using std::cin;

class Board
{//contains the levels, knows how to read new levels
public:
	Board(const int levelNum);
	virtual ~Board() = default;
	void readBoard(const int levelNum);
	void addToBoard(ifstream& input, char planet, int x, int y,int upgrades , int i);
	void drawBoard(sf::RenderWindow& window);
	void moveUnits();
	void openFile(ifstream& input, int levelNum);
	void makeAdjacencyList(stringstream& line);
	vector<sf::Vector2i> m_positions;//a vector that holds the row and col of each object
	void handleClick(const sf::Event& event, sf::RenderWindow& window);
	bool isLevelUp()const;
	void resetBoard();
	PlanetColor_t findColor(const char color);
private:
	vector<std::unique_ptr<Planet>> m_board;
	int m_level;
	vector<vector<int>> m_adjacencyList;
	bool m_levelUp = false;
	bool m_gameOver = false;

};

