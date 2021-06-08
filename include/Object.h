#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "utillities.h"

const int SMALLPLANET = 30;
const int MEDIUMPLANET = 50;
const int LARGEPLANET = 70;

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