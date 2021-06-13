#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class Graphic
{
public:
	static Graphic& PicturesObject();
	sf::Texture& getTexture(int texture);
	sf::Font& getFont();
	~Graphic() = default;

private:
	Graphic();
	std::vector<sf::Texture> m_textures;
	sf::Font m_font;
};