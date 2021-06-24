#pragma once
#include "Music.h"
#include "Graphic.h"
#include "utillities.h"
#include "Screen.h"
#include <vector>
#include <map>
using std::vector;
using std::pair;
using std::unique_ptr;
//----------------------------------------------------------------------
class Menu {
public:
	Menu();
	void openMenu();
	~Menu() = default;
	void loadMenuSprite();
	void loadLevelSprite();
	void addOptions();
	bool performAction();
	bool executeStart();
	bool executeLevel(); bool exitShop = false;
	bool executeInstructions();
	//void openInst();
	bool executeExit();
	//bool levelWindow();
	MenuOptions getSelected() { return m_selected; };
	LevelOptions getLevel() { return m_level; };
	void handleUp(int& candidate);
	void handleDown(int& candidate);
	void drawMenu(sf::RenderWindow& window, int candidate);
	void drawLevel(sf::RenderWindow& window);
	void checkIfcontains(sf::Vector2f& location, int& candidate);
	bool checkIfcontainsLevel(sf::Vector2f& location, bool &exitLevel);
private:
	sf::RenderWindow m_window;
	typedef pair<MenuOptions, bool(Menu::*)()> m_option;
	vector<m_option> m_options;
	std::array <sf::Sprite, Graphic::MENU_TEXTURES> m_MenuSprites;
	std::array <sf::Sprite, Graphic::LEVEL_TEXTURES> m_levelSprites;
	MenuOptions m_selected;
	LevelOptions m_level;
	Screen m_screen;
};