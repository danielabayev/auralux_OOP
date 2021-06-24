#include "..\include\Object.h"

Object::Object(const sf::Color& color) :m_color(color){}
//-----------------------------------------------------------------------------------------------
void Object::draw(sf::RenderWindow& window)const
{
	window.draw(m_circle);
}
//-----------------------------------------------------------------------------------------------
sf::Color Object::getColor()const
{
	return m_color;
}
//-----------------------------------------------------------------------------------------------
const sf::CircleShape& Object::getShape() const
{
	return m_circle;
}
//-----------------------------------------------------------------------------------------------
int Object::findColor(const sf::Color& color)const
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

