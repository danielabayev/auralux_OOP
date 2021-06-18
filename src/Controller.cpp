#include "Controller.h"

Controller::Controller() 
    :m_window(sf::VideoMode(STARTWIDTH, STARTHEIGHT), "Example"), 
     m_board(1),
     m_screen(STARTWIDTH,STARTHEIGHT)
{
    m_player = std::make_unique<Player>();
    m_opponents.resize(OPPONENTS);
    m_opponents[RED] = std::make_unique<Opponent>(sf::Color::Red);
    m_opponents[YELLOW] = std::make_unique<Opponent>(sf::Color::Yellow);
    m_opponents[GREEN] = std::make_unique<Opponent>(sf::Color::Green);
    m_opponents[CYAN] = std::make_unique<Opponent>(sf::Color::Cyan);
    srand(time(NULL));
    m_window.setFramerateLimit(30);
    readLevel();
    std::array <sf::Sprite, Graphic::MENU_TEXTURES> m_sprites;
    loadSprites();
    mainMenu(false);
    while (m_window.isOpen())
    {
        run();
        mainMenu(true);
    }
}
//-----------------------------------------------------------------
void Controller::loadSprites()
{
    for (int i = 0; i < Graphic::PicturesObject().MENU_TEXTURES; i++)
        m_sprites[i].setTexture(Graphic::PicturesObject().getTexture(i));
    m_sprites[1].setPosition((float)STARTWIDTH / 2 - m_sprites[1].getGlobalBounds().width / 2, 90.f);
    for (size_t i = 2; i < m_sprites.size() - 1; i += 2)
    {
        m_sprites[i].setPosition((float)STARTWIDTH /2 - m_sprites[i].getGlobalBounds().width / 2, 280.f + i * 60.f);
        m_sprites[i + 1].setPosition((float)STARTWIDTH / 2 - m_sprites[i + 1].getGlobalBounds().width / 2,
            280.f + i * 60.f);
    }
}
//------------------------------------------------------------------------------
void Controller::run()
{
    while (m_window.isOpen())
    {
        m_window.clear();
        m_screen.drawBackground(m_window);
        drawPlanets(m_window);
        m_window.display();

        generate();
        moveUnits();
        checkForNewPlanets();

        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
                handleClick(event, m_window);//update player choice
            }
        }
    }
}
//------------------------------------------------------------
void Controller::mainMenu(bool gameOver)
{
    auto option = -1, candidate = (int)Menu::START;
    //Music::instance().startMenuSound();
    while (m_window.isOpen() && option == -1)
    {
        m_window.clear();
        m_window.draw(m_sprites[0]);
        Graphic::PicturesObject().getTexture(0).setRepeated(true);
        if ((0 - m_sprites[0].getPosition().x) == m_sprites[0].getTextureRect().width - STARTWIDTH)
            m_sprites[0].setPosition(0.f, 0.f);
        m_sprites[0].move(sf::Vector2f(5.f, 0.f));
        m_window.draw(m_sprites[0]);
        m_sprites[0].move(sf::Vector2f(-10.f, 0.f));
        m_window.draw(m_sprites[1]);
        for (int i = 2; i < m_sprites.size() - 1; i += 2)
            m_window.draw(m_sprites[(i == candidate) ? i + 1 : i]);
        m_window.display();
   
        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
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

                checkIfcontains(location, option);
                //Music::instance().startClickSound();
                break;
            }
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Key::Up:
                   //Music::instance().startClickSound();
                    candidate = (int)Menu::START;
                    break;
                case sf::Keyboard::Key::Down:
                   // Music::instance().startClickSound();
                    candidate = (candidate == (int)Menu::START) ? (int)Menu::EXIT :
                        (int)Menu::START;
                    break;
                case sf::Keyboard::Key::Enter:
                    //Music::instance().startClickSound();
                    option = candidate;
                    break;
                }
                break;
            }
        }
    }
    if (option == (int)Menu::EXIT)
        m_window.close();
}
//-------------------------------------------------------------------------
void Controller::checkIfcontains(sf::Vector2f location, int& wantedValue)
{
    for (int i = 2; i < m_sprites.size(); i += 2)
        if (m_sprites[i].getGlobalBounds().contains(location))
        {
            wantedValue = i;
            //Music::instance().startClickSound();
            break;
        }
}
//---------------------------------------------------------------------------------
void Controller::readLevel()
{
    m_board.resetBoard();
    resetData();
    m_planets = m_board.readBoard(m_level);

    for (auto& p : m_planets)
    {
        if (p->getColor() == sf::Color::Blue)
            m_player->addPlanet(p.get());
        else
        {
            for (auto& opp : m_opponents)
                if (p->getColor() == opp->getColor())
                {
                    opp->addPlanet(p.get());
                }
        }
    }
}
//-------------------------------------------------------------------------
void Controller::resetData()
{
    m_player->resetData();
    for (auto& opp : m_opponents)
        opp->resetData();
}
//-------------------------------------------------------------------------------------
void Controller::handleClick(const sf::Event& event, sf::RenderWindow& window)
{
    auto location = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });

    std::pair<bool, int> controlled;
    controlled = m_player->controlled();
    if (!controlled.first)
    {
        for (int i = 0; i < m_planets.size(); i++)
            if (m_planets[i]->getPlanet().getShape().getGlobalBounds().contains(location))
            {
                if (m_player->checkIfBelongs(m_planets[i].get()))
                {
                    m_player->setControlled(true, i);
                    break;
                }
            }

    }
    else
    {
        for (auto& planet : m_planets)
            if (planet->getPlanet().getShape().getGlobalBounds().contains(location))
            {
                if (planet == m_planets[controlled.second])
                    planet->determineAction();
                else
                    m_planets[controlled.second]->move(*planet);
                
                m_player->setControlled(false, -1);
                //temp - should to be in the player?
            }

    }
}
//-----------------------------------------------------------------------------------
void Controller::checkForNewPlanets()
{
    for (auto& p : m_planets)
    {
        if (p->getColor() == sf::Color::Blue && !(m_player->checkIfBelongs(p.get())))
            m_player->addPlanet(p.get());
    }
}

void Controller::drawPlanets(sf::RenderWindow& window)
{
    for (auto& p : m_planets)
    {
        p->draw(window);
    }
}

void Controller::generate()
{
    for (auto& planet : m_planets)
        planet->generateUnits();
}

void Controller::moveUnits()
{
    for (int i = 0; i < m_planets.size(); i++)
    {
        m_planets[i]->move(*m_planets[i]);
        if (m_planets[i]->getNeedToMove())
            m_planets[i]->moveOwnerships(m_planets);
    }
}