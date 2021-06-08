#include "Board.h"
#include <SFML/Graphics.hpp>

//-----------------------------------------------------------------------------
Board::Board(const int levelNum)
{
	//m_font.loadFromFile("C:/Windows/Fonts/SHOWG.TTF");
	//m_showTime.setFillColor(sf::Color::Red);
	//m_showTime.setFont(m_font);
	readBoard(levelNum);
};
//-----------------------------------------------------------------------------
void Board::readBoard(const int levelNum)
{
	ifstream file;
	try {
		int amount;
		char planet;
		int upgrades;
		int x, y;
		openFile(file, levelNum);
		auto check = file.peek();
		if (!isdigit(check))
			throw std::invalid_argument("wrong size argument , please enter a positive number\n");
		file >> amount;
		m_board.resize(amount);
		file.get();
		for (size_t i = 0; i < amount; i++)
		{
			if (file.eof())
				throw std::runtime_error("not enough lines in file\n");
			file >> planet;
			if (isdigit(planet))
				//throw std::invalid_argument("invalid argument in line: " + std::to_string((i + 1) * (j + 1)) + "\n");
				throw std::invalid_argument("invalid argument in line: " + std::to_string((i + 1) * (i + 1)) + "\n");
			if (file.eof())
				throw std::runtime_error("not enough lines or arguments in file\n");
			file >> x , y , upgrades;
			addToBoard(file, planet, x , y, upgrades , i);
			
		}
	}
	catch (const std::exception& t)
	{
		file.close();
		throw;
	}

	file.close();
}

//--------------------------------------------------------------------------
void Board::openFile(ifstream& input, int level)
{
	string fileName = std::to_string(level) + ".txt";
	input.open(fileName);
	if (!input.is_open())
		throw std::runtime_error("could not open file\n");
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Board::addToBoard(ifstream& input, char planet, int x,int y ,int upgrades , int i)
{
	PlanetColor_t color;
	stringstream line;
	string adjacency;
	sf::Vector2f pos(x,y);
	color = findColor(planet);
	if (color == BLUE_BIG)
		m_board[i] = std::make_unique<Planet>(sf::Color::Blue,upgrades , pos);

	else if (color == RED_BIG)
		m_board[i] = std::make_unique<Planet>(sf::Color::Red, upgrades, pos);

	else if (color == YELLOW_BIG)
		m_board[i] = std::make_unique<Planet>(sf::Color::Yellow, upgrades, pos);

	else if (color == EMPTY)
		m_board[i] = std::make_unique<Planet>(sf::Color::White, upgrades, pos);

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
//this needs to be fixed. wrong planet.
void Board::handleClick(const sf::Event& event, sf::RenderWindow& window)
{
//	Unit unit(sf::Color::Blue, PLAYER_OWN, m_planet);
	int button;
	if (event.mouseButton.button == sf::Mouse::Left)
		button = 15;//to delete
//		unit.defineTowards(m_planet);
}
//--------------------------------------------------------------------------
/*//this functions draws each one of the objects in the board
void Board::drawBoard(sf::RenderWindow& window)
{
	for (int i = 0; i < m_board.size(); i++)
	{
		for (int j = 0; j < m_board[i].size(); j++)
		{
			m_board[i][j]->draw(window);
		}
	}
	window.display();
}*/
//--------------------------------------------------------------------------
bool Board::isLevelUp() const
{
	return m_levelUp;
}
//--------------------------------------------------------------------------
//resets all the objects of the board class before reading a new level
void Board::resetBoard()
{
	m_board.clear();
	m_adjacencyList.clear();
	//m_size = 0;
	m_levelUp = false;
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
}