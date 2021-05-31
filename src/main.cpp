#include "Object.h"
#include "Planet.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode(600, 600), "Example");
    
    Planet p(sf::Color::Blue,PLANET,3);

    while (window.isOpen())
    {
        window.clear();
        p.draw(window);
        window.display();

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
