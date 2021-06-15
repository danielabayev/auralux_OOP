#include "Board.h"
#include <SFML/Graphics.hpp>
#include "Unit.h"
//-----------------------------------------------------------------------------
Board::Board(const int levelNum)
{
	//m_font.loadFromFile("C:/Windows/Fonts/SHOWG.TTF");
	//m_showTime.setFillColor(sf::Color::Red);
	//m_showTime.setFont(m_font);
	//readBoard(levelNum);
};
//-----------------------------------------------------------------------------
vector<std::shared_ptr<ManagePlanet>> & Board::readBoard(const int levelNum)
{
	//vector<std::shared_ptr<ManagePlanet>> mp;
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
			file >> x;
			file >> y;
			file >> upgrades;
			addToBoard(file, planet, x, y, upgrades, i);

		}
	}
	catch (const std::exception& t)
	{
		file.close();
		throw;
	}

	file.close();

	return m_board;
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
void Board::addToBoard(ifstream& input, char planet, int x, int y, int upgrades, int i)
{
	PlanetColor_t color;
	stringstream line;
	string adjacency;
	sf::Vector2f pos(x, y);
	color = findColor(planet);
	if (color == BLUE_BIG)
		m_board[i] = std::make_shared<ManagePlanet>(sf::Color::Blue, upgrades, pos);

	else if (color == RED_BIG)
		m_board[i] = std::make_shared<ManagePlanet>(sf::Color::Red, upgrades, pos);

	else if (color == YELLOW_BIG)
		m_board[i] = std::make_shared<ManagePlanet>(sf::Color::Yellow, upgrades, pos);

	else if (color == EMPTY)
		m_board[i] = std::make_shared<ManagePlanet>(sf::Color::White, upgrades, pos);

	std::getline(input, adjacency);
	line << adjacency;
	makeAdjacencyList(line);
}

/*void Board::drawBoard(sf::RenderWindow& window)
{
	for (int i = 0; i < m_board.size(); i++)
	{
		m_board[i]->draw(window);
	}
}

void Board::moveUnits()
{
	for (int i = 0; i < m_board.size(); i++)
	{
		m_board[i]->move(*m_board[i]);
		if (m_board[i]->getNeedToMove())
			m_board[i]->moveOwnerships(m_board);
	}
}
*/
/*void Board::generate()
{
	for (auto& planet : m_board)
		planet->generateUnits();
}
*/
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
/*void Board::handleClick(const sf::Event& event, sf::RenderWindow& window)
{
	auto location = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });

	if (!m_controlled)
	{
		for (int i = 0; i < m_board.size(); i++)
			if (m_board[i]->getPlanet().getShape().getGlobalBounds().contains(location))
			{
				m_controlled = true;
				m_controlledIndex = i;
				break;
			}
					
	}
	else
	{
		for (auto& planet : m_board)
			if (planet->getPlanet().getShape().getGlobalBounds().contains(location))
			{
				m_board[m_controlledIndex]->move(*planet);
				m_controlled = false;
			}

	}
		
}
*/

//--------------------------------------------------------------------------
bool Board::isLevelUp() const
{
	return m_levelUp;
}
//--------------------------------------------------------------------------

void Board::resetBoard()
{
	m_adjacencyList.clear();
	//���� ���� ������
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