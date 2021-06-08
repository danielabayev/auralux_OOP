#include "..\include\Object.h"

Object::Object(sf::Color color, int kind) :m_color(color)
{
	if (kind == PLANET)
		m_circle.setRadius(SMALLPLANET);
	else
		m_circle.setRadius(2);
	m_circle.setFillColor(color);
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
}
