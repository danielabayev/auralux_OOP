#include "Screen.h"

Screen::Screen(int width, int height)
	:// m_menuScreen(sf::VideoMode(700,500),"menu"),
	  m_background(sf::Sprite(Graphic::PicturesObject().getTexture(STARTBACKGROUND)))
{
	//set the start button
	m_start.setFont(Graphic::PicturesObject().getFont());
	m_start.setString("start");
	m_start.setFillColor(sf::Color::Blue);
	m_start.setCharacterSize(70);
	sf::FloatRect bounds = m_start.getGlobalBounds();
	m_start.setPosition(width / 2, height * 1 / 5);
	m_start.setOrigin(bounds.width / 2, bounds.height / 2);
	
	//set the speed button
	m_speed.setFont(Graphic::PicturesObject().getFont());
	m_speed.setString("speed");
	m_speed.setFillColor(sf::Color::Blue);
	m_speed.setCharacterSize(70);
	bounds = m_speed.getGlobalBounds();
	m_speed.setPosition(width / 2, height * 2 / 5);
	m_speed.setOrigin(bounds.width / 2, bounds.height / 2);

	//set the level button
	m_level.setFont(Graphic::PicturesObject().getFont());
	m_level.setString("level");
	m_level.setFillColor(sf::Color::Blue);
	m_level.setCharacterSize(70);
	bounds = m_level.getGlobalBounds();
	m_level.setPosition(width / 2, height * 3 / 5);
	m_level.setOrigin(bounds.width / 2, bounds.height / 2);

	m_rightArrow.setTexture(Graphic::PicturesObject().getTexture(RIGHTARROW));
	m_leftArrow.setTexture(Graphic::PicturesObject().getTexture(RIGHTARROW));
	m_leftArrow.setRotation(180);
	m_rightArrow.setPosition(150, 150);
	m_leftArrow.setPosition(350, 150);
	
}

void Screen::drawMenu(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_start);
	window.draw(m_speed);
	window.draw(m_level);
}

void Screen::drawLevel(sf::RenderWindow& window)
{
	window.draw(m_rightArrow);
	window.draw(m_leftArrow);
}

void Screen::drawBackground(sf::RenderWindow& window)
{
	window.draw(m_background);
}

Menuscreen Screen::checkMenu(const sf::Event& event, sf::RenderWindow& window)
{
	auto location = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
	if (m_level.getGlobalBounds().contains(location))
		return LEVEL;
	if (m_speed.getGlobalBounds().contains(location))
		return SPEED;
	if (m_start.getGlobalBounds().contains(location))
		return START;
	else
		return DIDNTCHOOSE;
}
