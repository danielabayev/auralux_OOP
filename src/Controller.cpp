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
    m_opponents[CYAN] = std::make_unique<Opponent>(sf::Color::Cyan);
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
    m_window.create(sf::VideoMode(STARTWIDTH, STARTHEIGHT), "AURALUX");
    m_window.setFramerateLimit(30);
    sf::Event event;
    sf::Clock clock;
    sf::Time timePassed;
    while (m_window.isOpen())
    {
        m_window.clear();
        m_screen.drawBackground(m_window);
        drawPlanets(m_window);
        m_window.display();
        timePassed = m_clock.restart();
        timePassed *= 15.f;
        generate();
        moveUnits(timePassed);
        checkCollisions();
        checkForNewPlanets();

        for (auto& oppo : m_opponents)
            oppo->nextMove(timePassed);
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
                handleClick(event, m_window);//update player choice
            }
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
//----------------------------------------------------------------------
void Controller::checkCollisions()
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
//---------------------------------------------------------------------
void Controller::moveUnits(sf::Time timePassed)
{
    for (int i = 0; i < m_planets.size(); i++)
    {
        if(m_planets[i]->getPlanet().getActive())
            m_planets[i]->move(*m_planets[i] , timePassed);
    }
}
