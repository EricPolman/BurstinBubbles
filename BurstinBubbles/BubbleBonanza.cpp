#include <SFML/Graphics.hpp>

#include "stdafx.h"

int main()
{
    sf::RenderWindow Window(sf::VideoMode(800, 600), "Bubble Bonanza");
    
    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

		Window.clear(sf::Color::Blue);
        Window.display();
    }

    return 0;
}