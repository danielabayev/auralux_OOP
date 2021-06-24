#pragma once
#include "Board.h"
#include "Object.h"
#include "Planet.h"
#include "Screen.h"
#include "Player.h"
#include "Opponent.h"
#include "Music.h"
#include "Menu.h"

class Controller
{
public:
	Controller(); // ctor
	virtual ~Controller() = default;
	void run() ;
	void runGame();
	void readLevel();
	void resetData();
	void drawPlanets(sf::RenderWindow& window);
	void generate();
	void moveUnits(sf::Time timePassed);
	void checkCollisions();
	void handleClick(const sf::Event& event, sf::RenderWindow& window) ;
	void checkForNewPlanets();
private:
	sf::RenderWindow m_window;
	Board m_board;
	Screen m_screen;
	int m_level = 1;
	std::unique_ptr<Player> m_player;
	vector<std::unique_ptr<Opponent>> m_opponents;
	vector<std::unique_ptr<ManagePlanet>> m_planets;
	Menu m_menu;
	sf::Clock m_clock;
};