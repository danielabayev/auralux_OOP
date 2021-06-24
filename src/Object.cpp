#include "..\include\Object.h"

Object::Object(sf::Color color) :m_color(color)
{
	//m_circle.setFillColor(color);
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
}

sf::Color Object::getColor()const
{
	return m_color;
}

const sf::CircleShape& Object::getShape() const
{
	return m_circle;
}

int Object::findColor(sf::Color color)
{
	if (color == sf::Color::Blue)
		return BLUEP;
	else if (color == sf::Color::Red)
		return REDP;
	else if (color == sf::Color::Yellow)
		return YELLOWP;
	else if (color == sf::Color::Green)
		return GREENP;
	else
		return GREYP;

}

