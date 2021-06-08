#include "Object.h"
#include "Planet.h"
#include "Board.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    auto window = sf::RenderWindow(sf::VideoMode(600, 600), "Example");
    Board b(1);
   // Planet p(sf::Color::Blue, PLANET, 3, PLAYER_OWN);
   // Planet newPlanet(sf::Color::Magenta, PLANET, 2, FIRST_COMPUTER_OWN);
   // newPlanet.setPosition(sf::Vector2f(100,100));
   // Unit check_unit(sf::Color::Magenta, UNIT, &p);
    window.setFramerateLimit(30);
    bool tmp = true;
    while (window.isOpen())
    {
        window.clear();
       // p.draw(window);
      //  newPlanet.draw(window);
      //  check_unit.draw(window);
        window.display();
      //  if (tmp)
          //  check_unit.move(&p);
        //else
           // check_unit.move(&newPlanet);
      //  p.move(p);
       
        if (auto event = sf::Event{}; window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                tmp = true;
               // check_unit.defineTowards(&newPlanet);
               // tmp = !tmp;
            }
        }
    }
}
