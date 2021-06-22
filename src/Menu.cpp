#include "..\include\Menu.h"
Menu::Menu()
{
    loadMenuSprite();
    addOptions();
}
void Menu::openMenu()
{
    m_window.create(sf::VideoMode(STARTWIDTH, STARTHEIGHT), "MENU");
    m_window.setPosition(sf::Vector2i(m_window.getPosition().x, 0));
    auto option = -1, candidate = (int)MenuOptions::START;
    Graphic::PicturesObject().getTexture(0).setRepeated(true);
    drawMenu(m_window, candidate);
    //Music::instance().startMenuSound();
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
                    m_window.close();
                    return;
                }
                m_window.clear();
                drawMenu(m_window, candidate);
                m_window.display();
            }
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Key::Up:
                    //Music::instance().startClickSound();
                    handleUp(candidate);
                    break;
                case sf::Keyboard::Key::Down:
                    // Music::instance().startClickSound();
                    handleDown(candidate);
                    break;
                case sf::Keyboard::Key::Enter:
                    //Music::instance().startClickSound();
                    option = candidate;
                    if (performAction())
                    {
                        m_window.close();
                        return;
                    }
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
        m_MenuSprites[i].setTexture(Graphic::PicturesObject().getTexture(i));
    m_MenuSprites[1].setPosition((float)STARTWIDTH / 2 - m_MenuSprites[1].getGlobalBounds().width / 2, 90.f);
    for (size_t i = 2; i < m_levelSprites.size() - 1; i += 2)
    {
        m_MenuSprites[i].setPosition((float)STARTWIDTH / 2 - m_MenuSprites[i].getGlobalBounds().width / 2, 270.f + i * 50.f);
        m_MenuSprites[i + 1].setPosition((float)STARTWIDTH / 2 - m_MenuSprites[i + 1].getGlobalBounds().width / 2,
            270.f + i * 50.f);
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Menu::addOptions()
{
	m_options.emplace_back(m_option(MenuOptions::START, &Menu::executeStart));
	m_options.emplace_back(m_option(MenuOptions::LEVEL, &Menu::executeLevel));
	m_options.emplace_back(m_option(MenuOptions::SPEED, &Menu::executeSpeed));
	m_options.emplace_back(m_option(MenuOptions::EXIT, &Menu::executeExit));
}

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
//int Menu::getOptionFromUser()
//{
//
//}
//---------------------------------------------------------------------------
bool Menu::executeStart()
{
    m_selected = MenuOptions::START;
    return true;
}
//---------------------------------------------------------------------------
bool Menu::executeLevel()
{
    m_window.clear();
    drawLevel(m_window);
    m_window.display();
    while (m_window.isOpen())
    {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_selected = MenuOptions::EXIT;
                m_window.close();
                break;
            }
        }
    }
    return true;

}
//---------------------------------------------------------------------------
bool Menu::executeSpeed()
{
    return false;
}
//---------------------------------------------------------------------------
bool Menu::executeExit()
{
    m_selected = MenuOptions::EXIT;
    return true;
}
//------------------------------------------------------------------------------
void Menu::handleUp(int& candidate)
{
    if (candidate == (int)MenuOptions::EXIT)
        candidate = (int)MenuOptions::SPEED;
    else if (candidate == (int)MenuOptions::SPEED)
        candidate = (int)MenuOptions::LEVEL;
    else if (candidate == (int)MenuOptions::LEVEL)
        candidate = (int)MenuOptions::START;
}
//---------------------------------------------------------------------------
void Menu::handleDown(int& candidate)
{
    if (candidate == (int)MenuOptions::START)
        candidate = (int)MenuOptions::LEVEL;
    else if (candidate == (int)MenuOptions::LEVEL)
        candidate = (int)MenuOptions::SPEED;
    else if (candidate == (int)MenuOptions::SPEED)
        candidate = (int)MenuOptions::EXIT;
    else if (candidate == (int)MenuOptions::EXIT)
        candidate = (int)MenuOptions::START;
}

void Menu::drawMenu(sf::RenderWindow& window, int candidate)
{
    window.draw(m_MenuSprites[0]);
    if ((0 - m_MenuSprites[0].getPosition().x) == m_MenuSprites[0].getTextureRect().width - STARTWIDTH)
        m_MenuSprites[0].setPosition(0.f, 0.f);
    m_MenuSprites[0].move(sf::Vector2f(5.f, 0.f));
    window.draw(m_MenuSprites[0]);
    m_MenuSprites[0].move(sf::Vector2f(-10.f, 0.f));
    window.draw(m_MenuSprites[1]);
    for (int i = 2; i < m_MenuSprites.size() - 1; i += 2)
        window.draw(m_MenuSprites[(i == candidate) ? i + 1 : i]);
}
//-------------------------------------------------------------------------
void Menu::drawLevel(sf::RenderWindow& window)
{
    window.draw(m_MenuSprites[0]);

}
//-------------------------------------------------------------
void Menu::checkIfcontains(sf::Vector2f &location, int &candidate)
{
    for (int i = 2; i < m_MenuSprites.size(); i += 2)
        if (m_MenuSprites[i].getGlobalBounds().contains(location))
        {
            candidate = i;
            m_selected = static_cast<MenuOptions>(i);
            break;
        }
}
//---------------------------------------------------------------------------------