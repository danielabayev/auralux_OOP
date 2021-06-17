#pragma once
#include "Board.h"
#include "Object.h"
#include "Planet.h"
#include "Screen.h"
#include "Player.h"
#include "Opponent.h"
//#include "Music.h"

class Controller
{
public:
	Controller(); // ctor
	void loadSprites();
	virtual ~Controller() = default;
	void run() ;
	void mainMenu(bool gameOver);
	void checkIfcontains(sf::Vector2f location, int& wantedValue);
	void readLevel();
	void resetData();

	
	void drawPlanets(sf::RenderWindow& window);
	void generate();
	void moveUnits();
	void handleClick(const sf::Event& event, sf::RenderWindow& window) ;

	void checkForNewPlanets();

private:
	std::array <sf::Sprite, Graphic::MENU_TEXTURES> m_sprites;
	sf::RenderWindow m_window;
	Board m_board;
	Screen m_screen;
	int m_level = 1;
	std::unique_ptr<Player> m_player;
	vector<std::unique_ptr<Opponent>> m_opponents;
	vector<std::unique_ptr<ManagePlanet>> m_planets;
};