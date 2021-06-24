#include "..\include\Menu.h"
Menu::Menu():m_screen(STARTWIDTH, STARTHEIGHT)
{
    loadMenuSprite();
    loadLevelSprite();
    addOptions();
}
//-------------------------------------------------------------------------
void Menu::openMenu()
{
    m_window.create(sf::VideoMode(STARTWIDTH, STARTHEIGHT), "MENU");
    m_window.setPosition(sf::Vector2i(m_window.getPosition().x, 0));
    auto option = -1, candidate = (int)MenuOptions::START;
    Graphic::PicturesObject().getTexture(0).setRepeated(true);
    drawMenu(m_window, candidate);
    Music::instance().startMenuSound();
    while (m_window.isOpen() && option == -1)
    {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_selected = MenuOptions::EXIT;
                m_window.close();
                return;
            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseMove.x, event.mouseMove.y });
                checkIfcontains(location, candidate);
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                checkIfcontains(location, candidate);
                if (performAction())
                {
                    Music::instance().pauseMenuMusic();
                    m_window.close();
                    return;
                }
                m_window.clear();
                drawMenu(m_window, candidate);
                m_window.display();
            }
            }
        }
        m_window.clear();
        drawMenu(m_window, candidate);
        m_window.display();
    }
}
//-------------------------------------------------------------------------------------------------------
void Menu::loadMenuSprite()
{
		for (int i = 0; i < Graphic::PicturesObject().MENU_TEXTURES; i++)
			m_MenuSprites[i].setTexture(Graphic::PicturesObject().getTexture(i));
		m_MenuSprites[1].setPosition((float)STARTWIDTH / 2 - m_MenuSprites[1].getGlobalBounds().width / 2, 90.f);
		for (size_t i = 2; i < m_MenuSprites.size() - 1; i += 2)
		{
			m_MenuSprites[i].setPosition((float)STARTWIDTH / 2 - m_MenuSprites[i].getGlobalBounds().width / 2, 270.f + i * 50.f);
			m_MenuSprites[i + 1].setPosition((float)STARTWIDTH / 2 - m_MenuSprites[i + 1].getGlobalBounds().width / 2,
				270.f + i * 50.f);
		}
}
//---------------------------------------------------------------------------------------------------------------------
void Menu::loadLevelSprite()
{
    for (int i = 0; i < Graphic::PicturesObject().LEVEL_TEXTURES; i++)
    {
        m_levelSprites[i].scale(0.3, 0.3);
        m_levelSprites[i].setTexture(Graphic::PicturesObject().getLevelTexture(i));
    }
    m_levelSprites[0].scale(2, 2);
    m_levelSprites[1].scale(1.3, 1.3);
    m_levelSprites[1].setPosition((float)STARTWIDTH / 2 - m_levelSprites[1].getGlobalBounds().width / 2, 40.f);
    m_levelSprites[2].setPosition(30.f,20.f);
    m_levelSprites[3].setPosition(50, 250.f);
    m_levelSprites[4].setPosition(270, 250.f);
    m_levelSprites[5].setPosition(490, 250.f);
    m_levelSprites[6].setPosition(50, 540.f);
    m_levelSprites[7].setPosition(270, 540.f);
    m_levelSprites[8].setPosition(490, 540.f);
}
//----------------------------------------------------------------------------------------------------------------------
void Menu::addOptions()
{
	m_options.emplace_back(m_option(MenuOptions::START, &Menu::executeStart));
	m_options.emplace_back(m_option(MenuOptions::LEVEL, &Menu::executeLevel));
	m_options.emplace_back(m_option(MenuOptions::INSTRUCTIONS, &Menu::executeInstructions));
	m_options.emplace_back(m_option(MenuOptions::EXIT, &Menu::executeExit));
}
//---------------------------------------------------------------------------------
bool Menu::performAction()
{
    for(int i = 0; i < m_options.size(); i++)
        if (m_options[i].first == m_selected)
        {
            return(this->*m_options[i].second)();
        }
    return false;
}
//---------------------------------------------------------------------------
bool Menu::executeStart()
{
    m_selected = MenuOptions::START;
    return true;
}
//---------------------------------------------------------------------------
bool Menu::executeLevel()
{
    m_selected = MenuOptions::LEVEL;
    bool exitLevel = false;
    drawLevel(m_window);
    while (true)
    {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_selected = MenuOptions::EXIT;
                m_window.close();
                return true;

                //if the mouse press handle.
            case sf::Event::MouseButtonReleased:
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                if (checkIfcontainsLevel(location, exitLevel))
                {
                    if (m_level == LevelOptions::MENU)
                        break;
                    return true;
                }
            }
        }
        if (exitLevel)
            return false;

        drawLevel(m_window);
    }
}
//---------------------------------------------------------------------------
bool Menu::executeInstructions()
{
    sf::RenderWindow inst;
    sf::Sprite instBack;
    sf::Texture texture;
    texture.loadFromFile("instructions.png");
    instBack.setTexture(texture);
    instBack.setPosition(sf::Vector2f(0, 0));
    inst.create(sf::VideoMode(1050, 662), "instructions", sf::Style::Titlebar | sf::Style::Close);
    inst.clear();
    inst.draw(m_MenuSprites[0]);
    inst.draw(instBack);
    inst.display();

    while (inst.isOpen())
    {
        for (auto event = sf::Event{}; inst.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                inst.close();
                break;
            }
        }
    }
    return false;
}
//-----------------------------------------------------------------
bool Menu::executeExit()
{
    m_selected = MenuOptions::EXIT;
    return true;
}
//------------------------------------------------------------------------------
void Menu::handleUp(int& candidate)const
{
    if (candidate == (int)MenuOptions::EXIT)
        candidate = (int)MenuOptions::INSTRUCTIONS;
    else if (candidate == (int)MenuOptions::INSTRUCTIONS)
        candidate = (int)MenuOptions::LEVEL;
    else if (candidate == (int)MenuOptions::LEVEL)
        candidate = (int)MenuOptions::START;
}
//---------------------------------------------------------------------------
void Menu::handleDown(int& candidate)const
{
    if (candidate == (int)MenuOptions::START)
        candidate = (int)MenuOptions::LEVEL;
    else if (candidate == (int)MenuOptions::LEVEL)
        candidate = (int)MenuOptions::INSTRUCTIONS;
    else if (candidate == (int)MenuOptions::INSTRUCTIONS)
        candidate = (int)MenuOptions::EXIT;
    else if (candidate == (int)MenuOptions::EXIT)
        candidate = (int)MenuOptions::START;
}
//-------------------------------------------------------------------------
void Menu::drawMenu(sf::RenderWindow& window, int candidate)
{
    window.draw(m_MenuSprites[0]);
    if ((0 - m_MenuSprites[0].getPosition().x) == m_MenuSprites[0].getTextureRect().width - STARTWIDTH)
        m_MenuSprites[0].setPosition(0.f, 0.f);
    m_MenuSprites[0].move(sf::Vector2f(2.f, 0.f));
    window.draw(m_MenuSprites[0]);
    m_MenuSprites[0].move(sf::Vector2f(-3.f, 0.f));
    window.draw(m_MenuSprites[1]);
    for (int i = 2; i < m_MenuSprites.size() - 1; i += 2)
        window.draw(m_MenuSprites[(i == candidate) ? i + 1 : i]);
}
//-------------------------------------------------------------------------
void Menu::drawLevel(sf::RenderWindow& window)
{
    window.clear();
    m_screen.drawLevelScreen(window);
    for (int i = 0; i < m_levelSprites.size(); ++i)
    {
        window.draw(m_levelSprites[i]);
    }
    window.display();
}
//-------------------------------------------------------------
void Menu::checkIfcontains(const sf::Vector2f &location, int &candidate)
{
    for (int i = 2; i < m_MenuSprites.size(); i += 2)
        if (m_MenuSprites[i].getGlobalBounds().contains(location))
        {
            Music::instance().startClickSound();
            candidate = i;
            m_selected = static_cast<MenuOptions>(i);
            break;
        }
}
//---------------------------------------------------------------------------------
bool Menu::checkIfcontainsLevel(const sf::Vector2f& location, bool &exitLevel)
{
    for (int i = 2; i < m_levelSprites.size(); i++)
        if (m_levelSprites[i].getGlobalBounds().contains(location))
        {
            m_level  = static_cast<LevelOptions>(i);
            if (m_level == LevelOptions::MENU)
            {
                exitLevel = true;
                break;
            }
            return true;
        }
    return false;
}
//---------------------------------------------------------------------------------