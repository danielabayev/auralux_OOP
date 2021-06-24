#include "Graphic.h"
#include "utillities.h"

Graphic& Graphic::PicturesObject()
{
	static Graphic graphic;
	return graphic;
}
//-------------------------------------------------------------------
sf::Texture& Graphic::getTexture(int texture)
{
	return m_menuTextures[texture];
}
//-------------------------------------------------------------------
sf::Texture& Graphic::getLevelTexture(int texture)
{
	return m_levelTextures[texture];
}
//-------------------------------------------------------------------
sf::Texture& Graphic::getUpgradeTexture(int texture)
{
	if(texture == GREYP)
		texture = 0;
	return m_upgradeTextures[texture];
}
//-------------------------------------------------------------------
sf::Font& Graphic::getFont()
{
	return m_font;
}
//--------------------------------------------------------------------
Graphic::Graphic()
{
	loadMenuTextures();
	loadLevelTextures();
	loadUpgradeTextures();
	planets[BLUEP].loadFromFile("bluep.png");
	planets[REDP].loadFromFile("redp.png");
	planets[YELLOWP].loadFromFile("yellowp.png");
	planets[GREENP].loadFromFile("greenp.png");
	planets[GREYP].loadFromFile("greyp.png");

	m_particleTextures[BLUE1].loadFromFile("bluepar.png");
	m_particleTextures[RED1].loadFromFile("redpar.png");
	m_particleTextures[YELLOW1].loadFromFile("yellowpar.png");
	m_particleTextures[GREEN1].loadFromFile("greenpar.png");
	m_healthTexture.loadFromFile("redUpgrade.png");
}
//-----------------------------------------------------------------------------------------------
void Graphic::loadUpgradeTextures()
{
	std::array <std::string, UPGRADE_TEXTURES> upgradeName =
	{ "blueUpgrade", "orangeUpgrade", "yellowUpgrade", "greenUpgrade" };

	for (int i = 0; i < upgradeName.size(); i++)
		m_upgradeTextures[i].loadFromFile(upgradeName[i] + ".png");
}
//----------------------------------------------------------------------------------------------
void Graphic::loadMenuTextures()
{
	std::array <std::string, MENU_TEXTURES> texturesName =
	{ "Space", "Auralux", "startWhite", "startBlue", "levelWhite", "levelBlue", "instructionsWhite", "instructionsBlue","exitWhite", "exitBlue"};

	for (int i = 0; i < texturesName.size(); i++)
		m_menuTextures[i].loadFromFile(texturesName[i] + ".png");
}
//----------------------------------------------------------------------------------------------
void Graphic::loadLevelTextures()
{
	std::array <std::string, LEVEL_TEXTURES> levelName =
	{"LevelBackgroud", "Level", "BackToMenu","Pegasus", "Lupus", "Hercules", "Andromeda","Vergo", "Taurus"};

	for (int i = 1; i < levelName.size(); i++)
		m_levelTextures[i].loadFromFile(levelName[i] + ".png");
	m_levelTextures[0].loadFromFile(levelName[0] + ".jpg");
}
//-----------------------------------------------------------------------------------------------
sf::Texture& Graphic::getPlanet(int planet)
{
	return planets[planet];
}
sf::Texture& Graphic::getHealthTexture()
{
	return m_healthTexture;
}
sf::Texture& Graphic::getParticleTexture(int texture)
{
	if (texture > 3)
		texture = 0;
	return m_particleTextures[texture];
}
