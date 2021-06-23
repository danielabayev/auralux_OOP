#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <array>

class Graphic
{
public:
	const static auto MENU_TEXTURES = 10;
	const static auto LEVEL_TEXTURES = 8;
	const static auto UPGRADE_TEXTURES = 4;
	static Graphic& PicturesObject();
	sf::Texture& getPlanet(int planet);
	sf::Texture& getTexture(int texture);
	sf::Texture& getLevelTexture(int texture);
	sf::Texture& getUpgradeTexture(int texture);
	sf::Font& getFont();
	~Graphic() = default;

private:
	Graphic();
	std::array<sf::Texture, MENU_TEXTURES> m_menuTextures;
	std::array<sf::Texture, LEVEL_TEXTURES> m_levelTextures;
	std::array<sf::Texture, UPGRADE_TEXTURES> m_upgradeTextures;
	std::array<sf::Texture , 5> planets;
	sf::Font m_font;
	void loadMenuTextures();
	void loadLevelTextures();
	void loadUpgradeTextures();
};