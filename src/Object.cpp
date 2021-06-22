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

sf::CircleShape Object::getShape() const
{
	return m_circle;
}

