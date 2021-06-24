#include "Controller.h"

Controller::Controller() :
     m_board(1),
     m_screen(STARTWIDTH,STARTHEIGHT)
{
    m_player = std::make_unique<Player>();
    m_opponents.resize(OPPONENTS);
    m_opponents[RED] = std::make_unique<Opponent>(sf::Color::Red);
    m_opponents[YELLOW] = std::make_unique<Opponent>(sf::Color::Yellow);
    m_opponents[GREEN] = std::make_unique<Opponent>(sf::Color::Green);

    m_screens[GAMEOVER].setTexture(&(Graphic::PicturesObject().getScreenTexture(GAMEOVER)));
    m_screens[WIN].setTexture(&(Graphic::PicturesObject().getScreenTexture(WIN)));

    m_playerTarget.setFillColor(sf::Color::Transparent);
    m_playerTarget.setOutlineColor(sf::Color::White);
    m_playerTarget.setOutlineThickness(2);
    srand(time(NULL));
    readLevel();
    m_clock.restart();
}
//------------------------------------------------------------------------------
void Controller::run()
{
    while (true)
    {
        m_menu.openMenu();
        MenuOptions option = m_menu.getSelected();
        LevelOptions level = m_menu.getLevel();
        if (option == MenuOptions::EXIT)
            return;
        else if (option == MenuOptions::LEVEL)
        {
            m_level = (int)level - 2;
            readLevel();
            runGame();
        }
        else if (option == MenuOptions::START)
        {
            m_level = 1;
            readLevel();
            runGame();
        }
    }
}
//-----------------------------------------------------------
void Controller::runGame()
{
    Music::instance().startBackgroundMusic();
    m_window.create(sf::VideoMode(GAMEWIDTH, GAMEHEIGHT), "AURALUX");
    m_window.setFramerateLimit(30);
    sf::Time timePassed;
    while (m_window.isOpen())
    {
        m_window.clear();
        m_screen.drawBackground(m_window);
        drawPlanets(m_window);
        m_window.display();
        timePassed = m_clock.restart();
        timePassed *= 15.f;

        //the game loop
        generate();
        moveUnits(timePassed);
        checkCollisions();
        checkForNewPlanets();

        for (auto& oppo : m_opponents)
            oppo->nextMove(timePassed);
        
        //the player choice
        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                Music::instance().stopBackgroundMusic();
                Music::instance().startClickSound();
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
                handleClick(event, m_window);
            }
        }

        if (gameOver())
        {
            Music::instance().stopBackgroundMusic();
            Music::instance().startClickSound();
            m_window.close();
        }
    }
}
//--------------------------------------------------------------------------------
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
                    m_targeted = true;
                    setTargetCircle(*m_planets[i].get());
                    break;
                }
            }
    }
    else
    {
        for (auto& planet : m_planets)
            if (planet->getPlanet().getShape().getGlobalBounds().contains(location))
            {
                m_planets[controlled.second]->movePlayer(*planet);
                m_player->setControlled(false, -1);
                m_targeted = false;
            }
    }
}
//-----------------------------------------------------------------------------------
void Controller::checkForNewPlanets()
{
    for (auto& p : m_planets)
    {
        if (p->getColor() == sf::Color::Blue && !(m_player->checkIfBelongs(p.get())))
        {
            m_player->addPlanet(p.get());
            p->changePlanet(sf::Color::Blue);
        }
        else if (p->getColor() == sf::Color::White && m_player->checkIfBelongs(p.get()))
        {
            m_player->removePlanet(p.get());
            p->changePlanet(sf::Color::White);
        }
        else
        {
            for (auto& opp : m_opponents)
            {
                if (opp->getColor() == p->getColor() && !(opp->checkIfBelongs(p.get())))
                {
                    opp->addPlanet(p.get());
                    p->changePlanet(opp->getColor());
                    break;
                }
                else if (p->getColor() == sf::Color::White && opp->checkIfBelongs(p.get()))
                {
                    opp->removePlanet(p.get());
                    p->changePlanet(sf::Color::White);
                    break;
                }
            }
        }
    }
}
void Controller::setTargetCircle(const ManagePlanet& mp)
{
    m_playerTarget.setPosition(mp.getPlanet().getShape().getPosition());
    m_playerTarget.setRadius(mp.getPlanet().getShape().getRadius());
    m_playerTarget.setOrigin(mp.getPlanet().getShape().getOrigin());
}
bool Controller::gameOver()
{
    if (m_player->isEmpty())
    {
        gameOverScreen(GAMEOVER);
        return true;
    }
    else
    {
        for (auto& opp : m_opponents)
            if (!opp->isEmpty())
                return false;
        gameOverScreen(WIN);
        return true;
    }
        
    return false;
}
//----------------------------------------------------------------------
void Controller::gameOverScreen(Screens screen)
{
    sf::Clock clock;
    sf::Time timePassed;
    
    sf::Vector2f backgroundsize(GAMEWIDTH , GAMEHEIGHT);
    if (screen == WIN)
    {
        m_screens[WIN].setSize(backgroundsize);
        Music::instance().startWinSound();
    }
    else
    {
        m_screens[GAMEOVER].setSize(backgroundsize);
        Music::instance().startLoseSound();
    }

    clock.restart();
    timePassed = clock.getElapsedTime();
    while (timePassed.asSeconds() < 3)
    {
        m_window.clear();
        if (screen == WIN)
            m_window.draw(m_screens[WIN]);     
        else
            m_window.draw(m_screens[GAMEOVER]);
        m_window.display();
        timePassed = clock.getElapsedTime();
    }
    
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
void Controller::checkCollisions()const
{
    for (int i = 0; i < m_planets.size(); i++)
    {
        if (m_planets[i]->getPlanet().getActive())
        {
            for (int j = 0; j < m_planets.size(); j++)
            {
                m_planets[i]->findCollisions(*m_planets[j]);
            }
        }
    }
}
//-----------------------------------------------------------------
void Controller::drawPlanets(sf::RenderWindow& window)const
{
    for (auto& p : m_planets)
        p->draw(window);
    if (m_targeted)
        window.draw(m_playerTarget);
}

void Controller::generate()const
{
    for (auto& planet : m_planets)
        planet->generateUnits();
}
//---------------------------------------------------------------------
void Controller::moveUnits(sf::Time timePassed)const
{
    for (int i = 0; i < m_planets.size(); i++)
    {
        if(m_planets[i]->getPlanet().getActive())
            m_planets[i]->move(*m_planets[i] , timePassed);
    }
}
