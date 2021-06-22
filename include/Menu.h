#pragma once
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
	void activateOption();
	bool performAction();
	int getOptionFromUser();
	bool executeStart();
	bool executeLevel();
	bool executeSpeed();
	bool executeExit();
	MenuOptions getSelected() { return m_selected; };
	void handleUp(int& candidate);
	void handleDown(int& candidate);
	void drawMenu(sf::RenderWindow& window, int candidate);
	void drawLevel(sf::RenderWindow& window);
	void checkIfcontains(sf::Vector2f& location, int& candidate);
private:
	sf::RenderWindow m_window;
	typedef pair<MenuOptions, bool(Menu::*)()> m_option;
	vector<m_option> m_options;
	std::array <sf::Sprite, Graphic::MENU_TEXTURES> m_MenuSprites;
	std::array <sf::Sprite, Graphic::LEVEL_TEXTURES> m_levelSprites;
	MenuOptions m_selected;
};