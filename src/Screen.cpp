#include "Screen.h"

Screen::Screen(int height, int width) 
{}

Screen& Screen::instance()
{
	static Screen screen(STARTHEIGHT,STARTWIDTH);
	return screen;
	
}

void Screen::Update(sf::RenderWindow& window, float deltaTime)
{
	if (m_background1 < STARTWIDTH)
	{
		m_background1 -= m_speed * deltaTime;
	}
	else
	{
		m_background1 = 0;
	}
	m_background.setPosition(0, m_background1);

}

void Screen::Render(sf::RenderWindow& window)
{
	window.draw(m_background);
}

void Screen::drawBackground(sf::RenderWindow& window)
{
	window.draw(sf::Sprite(Graphic::PicturesObject().getTexture(0)));
}

void Screen::drawLevelScreen(sf::RenderWindow& window)
{
	window.draw(sf::Sprite(Graphic::PicturesObject().getLevelTexture(0)));
}


