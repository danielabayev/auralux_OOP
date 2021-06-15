#pragma once
#include "Board.h"
#include "Object.h"
#include "Planet.h"
#include "Screen.h"
#include "Player.h"
#include "Opponent.h"

class Controller
{//אחראי על השלב עצמו, עליית שלב וניהול המשחק
public:
	Controller(); // ctor
	virtual ~Controller() = default;
	void run();
	Menuscreen menuScreen();
	int levelScreen();
	void readLevel();
	void resetData();

	
	void drawPlanets(sf::RenderWindow& window);
	void generate();
	void moveUnits();
	void handleClick(const sf::Event& event, sf::RenderWindow& window);

private:
	sf::RenderWindow m_window;
	Board m_board;
	Screen m_screen;
	int m_level = 1;
	std::unique_ptr<Player> m_player;
	vector<std::unique_ptr<Opponent>> m_opponents;
	vector<std::shared_ptr<ManagePlanet>> m_planets;
};