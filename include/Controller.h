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
	Controller();
	virtual ~Controller() = default;
	void run() ;
	
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
	sf::CircleShape m_playerTarget;
	bool m_targeted = false;
	sf::RectangleShape m_screens[SCREENS];

	//private funcs:
	void runGame();
	void readLevel();
	void resetData();
	void drawPlanets(sf::RenderWindow& window)const;
	void generate()const;
	void moveUnits(sf::Time timePassed)const;
	void checkCollisions()const;
	void handleClick(const sf::Event& event, sf::RenderWindow& window);
	void checkForNewPlanets();
	void setTargetCircle(const ManagePlanet& mp);
	bool gameOver();
	void gameOverScreen(Screens screen);
	
};