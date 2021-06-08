#include "..\include\Object.h"

Object::Object(sf::Color color) :m_color(color)
{
/*	if (kind == PLANET)
		
	else
		*/
	m_circle.setFillColor(color);
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
}
