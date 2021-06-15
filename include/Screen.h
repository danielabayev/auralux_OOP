#pragma once
#include <SFML/Graphics.hpp>
#include "Graphic.h"
#include "utillities.h"

class Screen
{//singelton class - in charge of the menu screen
public:
	Screen(int width, int height);
	~Screen() = default;
	void drawMenu(sf::RenderWindow& window);
	void drawLevel(sf::RenderWindow& window);
	void drawBackground(sf::RenderWindow& window);
	Menuscreen checkMenu(const sf::Event& event, sf::RenderWindow& window);
private:
	//sf::RenderWindow m_menuScreen;
	sf::Sprite m_background;
	sf::Text m_start;
	sf::Text m_level;
	sf::Text m_speed;
	sf::Sprite m_rightArrow;
	sf::Sprite m_leftArrow;
};