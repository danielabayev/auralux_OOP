#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "utillities.h"

class Object
{
public:
	Object(sf::Color color, int kind);
	~Object() = default;
	virtual void draw(sf::RenderWindow& window);

protected:
	sf::CircleShape m_circle;
	sf::Color m_color;
	sf::Sprite m_objectPng;
};