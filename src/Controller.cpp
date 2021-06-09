#include "Controller.h"

Controller::Controller() : m_board(1)
{
}

void Controller::run()
{
    srand(time(NULL));
    auto window = sf::RenderWindow(sf::VideoMode(600, 600), "Example");

    window.setFramerateLimit(30);
    while (window.isOpen())
    {
        window.clear();
        m_board.drawBoard(window);
        window.display();
        
        m_board.generate();
        m_board.moveUnits();

        if (auto event = sf::Event{}; window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                m_board.handleClick(event, window);
              
            }
        }
    }
}
