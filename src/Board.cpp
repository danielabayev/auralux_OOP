#include "Board.h"
#include <SFML/Graphics.hpp>
#include "Unit.h"
//-----------------------------------------------------------------------------
Board::Board(const int levelNum)
{};
//-----------------------------------------------------------------------------
vector<std::unique_ptr<ManagePlanet>> Board::readBoard(const int levelNum)
{
	vector<std::unique_ptr<ManagePlanet>> mp;
	ifstream file;
	try {
		int amount;
		char planet;
		int upgrades = 0;
		int x = 0, y = 0;
		openFile(file, levelNum);
		auto check = file.peek();
		if (!isdigit(check))
			throw std::invalid_argument("wrong size argument , please enter a positive number\n");
		file >> amount;
		mp.resize(amount);
		file.get();
		for (size_t i = 0; i < amount; i++)
		{
			if (file.eof())
				throw std::runtime_error("not enough lines in file\n");
			file >> planet;
			if (isdigit(planet))
				throw std::invalid_argument("invalid argument in line: " + std::to_string((i + 1) * (i + 1)) + "\n");
			if (file.eof())
				throw std::runtime_error("not enough lines or arguments in file\n");
			file >> x;
			file >> y;
			file >> upgrades;
			addToBoard(file, planet, x, y, upgrades, i, mp);

		}
	}
	catch (const std::exception& t)
	{
		file.close();
		throw;
	}

	file.close();

	return mp;
}

//--------------------------------------------------------------------------
void Board::openFile(ifstream& input,const int level)
{
	string fileName = std::to_string(level) + ".txt";
	input.open(fileName);
	if (!input.is_open())
		throw std::runtime_error("could not open file\n");
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Board::addToBoard(ifstream& input, char planet, int x, int y, int upgrades, int i, vector<std::unique_ptr<ManagePlanet>>& mp)
{
	PlanetColor_t color;
	stringstream line;
	string adjacency;
	sf::Vector2f pos(x, y);
	color = findColor(planet);
	if (color == BLUE_BIG)
		mp[i] = std::make_unique<ManagePlanet>(sf::Color::Blue, upgrades, pos);

	else if (color == RED_BIG)
		mp[i] = std::make_unique<ManagePlanet>(sf::Color::Red, upgrades, pos);

	else if (color == YELLOW_BIG)
		mp[i] = std::make_unique<ManagePlanet>(sf::Color::Yellow, upgrades, pos);

	else if (color == EMPTY)
		mp[i] = std::make_unique<ManagePlanet>(sf::Color::White, upgrades, pos);

	std::getline(input, adjacency);
	line << adjacency;
	makeAdjacencyList(line);
}

//--------------------------------------------------------------------------
//this function updates the adjacency list , for each object it holds the "keys" of it's neighbours
void Board::makeAdjacencyList(stringstream& line)
{
	int key;
	vector<int> adjacency;
	while (!line.rdbuf()->in_avail() == 0)
	{
		line >> key;
		if (isalpha(key) || key < 0)
			throw std::invalid_argument("invalid argument in one of the lines\n");

		adjacency.push_back(key);
	}
	m_adjacencyList.push_back(adjacency);

}
//----------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool Board::isLevelUp() const
{
	return m_levelUp;
}
//--------------------------------------------------------------------------

void Board::resetBoard()
{
	m_adjacencyList.clear();
	//restart amount of enemy
}
//--------------------------------------------------------------------------
PlanetColor_t Board::findColor(const char color)
{
	switch (color)
	{
	case 'B':
		return BLUE_BIG;
		break;
	case 'R':
		return RED_BIG;
		break;
	case 'Y':
		return YELLOW_BIG;
		break;
	case 'E':
		return EMPTY;
		break;
	}
	//add defualt return
}