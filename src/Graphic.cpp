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
sf::Font& Graphic::getFont()
{
	return m_font;
}
//--------------------------------------------------------------------
Graphic::Graphic()
{
	loadMenuTextures();
	planets[BLUEP].loadFromFile("bluep.png");
	planets[REDP].loadFromFile("redp.png");
	planets[YELLOWP].loadFromFile("yellowp.png");
	planets[GREENP].loadFromFile("greenp.png");
	planets[GREYP].loadFromFile("greyp.png");
}
//-----------------------------------------------------------------------------------------------
void Graphic::loadMenuTextures()
{
	std::array <std::string, MENU_TEXTURES> texturesName =
	{ "Space", "Auralux", "startWhite", "startBlue", "levelWhite", "levelBlue", "speedWhite", "speedBlue","exitWhite", "exitBlue"};

	for (int i = 0; i < texturesName.size(); i++)
		m_menuTextures[i].loadFromFile(texturesName[i] + ".png");
}
//----------------------------------------------------------------------------------------------
void Graphic::loadLevelTextures()
{
	std::array <std::string, LEVEL_TEXTURES> levelName =
	{ "Level", "Pegasus", "Lupus", "Hercules"};

	for (int i = 0; i < levelName.size(); i++)
		m_menuTextures[i].loadFromFile(levelName[i] + ".png");
}
//-----------------------------------------------------------------------------------------------
sf::Texture& Graphic::getPlanet(int planet)
{
	return planets[planet];
}