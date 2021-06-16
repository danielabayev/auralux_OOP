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
	return m_textures[texture];
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
//	m_textures.resize(TEXTURES);
//	m_textures[STARTBACKGROUND].loadFromFile("background.jpg");
//	m_textures[RIGHTARROW].loadFromFile("right-arrow.png");
//	//m_textures[STARTBACKGROUND].loadFromFile("startbutton.png");
//	m_font.loadFromFile("sansation.ttf");
///*	m_textures[STARTBUTTON].loadFromFile("startbutton.png");
//	m_textures[SPEEDBUTTON].loadFromFile("speedbutton.png");
//	m_textures[LEVELBUTTON].loadFromFile("levelbutton.png");*/
}
//-----------------------------------------------------------------------------------------------
void Graphic::loadMenuTextures()
{
	std::array <std::string, MENU_TEXTURES> texturesName =
	{ "Space", "Auralux", "startWhite", "startBlue", "exitWhite", "exitBlue" };

	for (int i = 0; i < texturesName.size(); i++)
		m_textures[i].loadFromFile(texturesName[i] + ".png");
	//m_textures[0].setRepeated(true);
}
//-----------------------------------------------------------------------------------------------