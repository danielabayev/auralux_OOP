#include "Controller.h"

Controller::Controller() 
    :m_window(sf::VideoMode(STARTWIDTH, STARTHEIGHT), "Example"), 
     m_board(1),
     m_screen(STARTWIDTH,STARTHEIGHT)
{
    srand(time(NULL));
    m_window.setFramerateLimit(30);
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
        m_board.drawBoard(m_window);
        m_window.display();
        
        m_board.generate();
        m_board.moveUnits();

        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
                m_board.handleClick(event, m_window);//עדכון של השחקן של הבחירה
                
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
