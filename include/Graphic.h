#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <array>

class Graphic
{
public:
	const static auto MENU_TEXTURES = 6;
	static Graphic& PicturesObject();
	sf::Texture& getTexture(int texture);
	sf::Font& getFont();
	~Graphic() = default;

private:
	Graphic();
	std::array<sf::Texture, MENU_TEXTURES> m_textures;
	sf::Font m_font;
	void loadMenuTextures();
};