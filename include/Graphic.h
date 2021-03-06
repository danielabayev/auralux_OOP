#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <array>

class Graphic
{
public:
	const static auto MENU_TEXTURES = 10;
	const static auto LEVEL_TEXTURES = 9;
	const static auto UPGRADE_TEXTURES = 4;
	const static auto SCREENS = 2;
	static Graphic& PicturesObject();
	sf::Texture& getPlanet(int planet);
	sf::Texture& getHealthTexture();
	sf::Texture& getParticleTexture(int texture);
	sf::Texture& getTexture(int texture);
	sf::Texture& getLevelTexture(int texture);
	sf::Texture& getScreenTexture(int texture);
	sf::Texture& getUpgradeTexture(int texture);
	sf::Font& getFont();
	virtual ~Graphic() = default;

private:
	Graphic();
	std::array<sf::Texture, MENU_TEXTURES> m_menuTextures;
	std::array<sf::Texture, LEVEL_TEXTURES> m_levelTextures;
	std::array<sf::Texture, UPGRADE_TEXTURES> m_upgradeTextures;
	std::array<sf::Texture , 5> planets;
	std::array<sf::Texture, 4> m_particleTextures;
	std::array<sf::Texture, SCREENS> m_screenTextures;
	sf::Texture m_healthTexture;
	sf::Font m_font;
	void loadMenuTextures();
	void loadLevelTextures();
	void loadUpgradeTextures();
	void loadScreenTextures();
};