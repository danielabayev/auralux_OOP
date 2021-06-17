#pragma once

#include "Planet.h"
#include "Graphic.h"
#include "ManagePlanet.h"
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

	void openFile(ifstream& input,const int levelNum);
	//vector<std::shared_ptr<ManagePlanet>> readBoard(const int levelNum);
	vector<std::unique_ptr<ManagePlanet>> readBoard(const int levelNum);

	//void addToBoard(ifstream& input, char planet, int x, int y, int upgrades, int i, vector<std::shared_ptr<ManagePlanet>>&);
	void addToBoard(ifstream& input, char planet, int x, int y, int upgrades, int i, vector<std::unique_ptr<ManagePlanet>>&);
	PlanetColor_t findColor(const char color);
	void makeAdjacencyList(stringstream& line);
	void resetBoard();

	void drawBoard(sf::RenderWindow& window);
	void moveUnits();
	void handleClick(const sf::Event& event, sf::RenderWindow& window);
	void generate();
	
	bool isLevelUp()const;

	//vector<std::pair(sf::Color)

private:
	//vector<std::shared_ptr<ManagePlanet>> m_board;//shared ptr
	int m_level;
	vector<vector<int>> m_adjacencyList;
	bool m_levelUp = false;
	bool m_gameOver = false;
	

};


