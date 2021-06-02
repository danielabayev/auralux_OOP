#include "Object.h"
#include "Planet.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    auto window = sf::RenderWindow(sf::VideoMode(600, 600), "Example");
    
    Planet p(sf::Color::Blue,PLANET,3);
    window.setFramerateLimit(30);
    while (window.isOpen())
    {
        window.clear();
        p.draw(window);
        window.display();
        p.move();
        if (auto event = sf::Event{}; window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
    }
}
