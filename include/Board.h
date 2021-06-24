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

	vector<std::unique_ptr<ManagePlanet>> readBoard(const int levelNum);
	void resetBoard();

private:
	int m_level;
	//save the adj for it can be build in the end of the level read (it build with the planets)
	vector<vector<int>> m_adjacencyList;

	//private function:
	void openFile(ifstream& input,const int levelNum)const;


	void addToBoard(ifstream& input, char planet, int x, int y, int upgrades, int i, vector<std::unique_ptr<ManagePlanet>>&);
	PlanetColor_t findColor(const char color)const;
	void makeAdjacencyList(stringstream& line);
	void makeAdj(vector<std::unique_ptr<ManagePlanet>>&)const;
};


