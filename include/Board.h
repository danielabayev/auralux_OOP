#pragma once
#include "utillities.h"
#include "Object.h"
#include "Planet.h"
#include "Graphic.h"
#include "Unit.h"
#include<map>
#include<set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Object.h"
#include <memory>
#include <list>

using std::stringstream;
using std::ifstream;
using std::vector;
using std::string;
using std::cin;
using std::list;

class Board
{//contains the levels, knows how to read new levels
public:
	Board(const int levelNum);
	virtual ~Board() = default;
	void readBoard(const int levelNum);
	void setBoardSize();
	void addToBoard(ifstream& input, char planet, int key, int i, int j);
	void drawBoard(sf::RenderWindow& window);
	void openFile(ifstream& input, int levelNum);
	void makeAdjacencyList(stringstream& line);
	vector<sf::Vector2i> m_positions;//a vector that holds the row and col of each object
	sf::Vector2f getBoardSize()const;
	void handleClick(const sf::Event& event, sf::RenderWindow& window);
	bool isLevelUp()const;
	void resetBoard();
	PlanetColor_t findColor(const char color);
private:
	vector<vector<std::unique_ptr<Planet>>> m_board;
	int m_rows = 0;
	int m_cols = 0;
	int m_level;
	vector<vector<int>> m_adjacencyList;
	bool m_levelUp = false;
	bool m_gameOver = false;
	Planet* m_planet;

};

