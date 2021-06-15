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
}

void Controller::run()
{
    //make the controll planet , every cp gets his mp`s.

    Menuscreen choice = menuScreen();
    int a;
    while (choice != START && choice != CLOSE)
    {
        switch (choice)
        {
        case SPEED:
            a = 0;
            break;
        case LEVEL:
            a = 3;
            break;
        case START:
            a = 4;
            break;
        case CLOSE:
            m_window.close();
            break;
        default:
            break;
        }
    }

    /*while (m_window.isOpen())
    {
        m_window.clear();
        m_screen.draw(m_window);
        m_window.display();
        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }
    }*/
    
 
    while (m_window.isOpen())
    {
        m_window.clear();
        m_screen.drawBackground(m_window);
        drawPlanets(m_window);
        m_window.display();
        
        generate();
        moveUnits();

        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
                handleClick(event, m_window);//עדכון של השחקן של הבחירה
                
            }
        }
       // CP->makesomething();//in the enemy every 4 sec

        //update the current mp in cp
    }
}

Menuscreen Controller::menuScreen()
{
    while (m_window.isOpen())
    {
        m_window.clear();
        m_screen.drawMenu(m_window);
        m_window.display();
        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                return CLOSE;
            case sf::Event::MouseButtonReleased:
                return m_screen.checkMenu(event, m_window);
            }
        }
    }
    return CLOSE;
}

int Controller::levelScreen()
{
    while (m_window.isOpen())
    {
        m_window.clear();
        m_screen.drawLevel(m_window);
        m_window.display();
        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                return -1;
            case sf::Event::MouseButtonReleased:
                break;
               // return m_screen.checkLevel(event, m_window);
            }
        }
    }
}

void Controller::readLevel()
{
    m_board.resetBoard();
    resetData();
    m_planets = m_board.readBoard(m_level);

    for (auto& p : m_planets)
    {
        if (p->getColor() == sf::Color::Blue)
            m_player->addPlanet(p);
        else
        {
            for (auto &opp : m_opponents)
                if (p->getColor() == opp->getColor())
                {
                    opp->addPlanet(p);
                }
        } 
    }
}

void Controller::resetData()
{
    m_player->resetData();
    for (auto& opp : m_opponents)
        opp->resetData();
}

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
                m_player->setControlled(true, i);
                break;
            }

    }
    else
    {
        for (auto& planet : m_planets)
            if (planet->getPlanet().getShape().getGlobalBounds().contains(location))
            {
                m_planets[controlled.second]->move(*planet);
                m_player->setControlled(false, -1);
                //זמני
            }

    }
}

void Controller::drawPlanets(sf::RenderWindow& window)
{
    for (auto &p:m_planets)
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
