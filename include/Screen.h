#pragma once
#include <SFML/Graphics.hpp>
#include "Graphic.h"
#include "utillities.h"

class Screen
{//singelton class - in charge of the menu screen
public:
	Screen(int height, int width);
	static Screen& instance();
	~Screen() = default;
	void Update(sf::RenderWindow& window, float deltaTime);
	void drawLevel(sf::RenderWindow& window);
	void drawBackground(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);
	//Menuscreen checkMenu(const sf::Event& event, sf::RenderWindow& window);
private:
	//sf::RenderWindow m_menuScreen;
	float m_background1;
	float m_background2;
	sf::Text m_start;
	sf::Text m_level;
	float m_speed;
	sf::Sprite m_background;
	//sf::Sprite m_rightArrow;
	//sf::Sprite m_leftArrow;
	sf::Vector2f m_size;
	sf::Sprite m_sprite1;
	sf::Sprite m_sprite2;

};