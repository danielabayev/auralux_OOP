#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

class Object
{
public:
	Object();
	~Object();

private:
	sf::Color m_color;
	sf::Sprite m_objectPng;
};