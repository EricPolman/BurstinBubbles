#include <SFML/Graphics.hpp>

#include "stdafx.h"
#include "Game.h"

int main()
{
    sf::RenderWindow Window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bubble Bonanza");
    sf::Clock deltaClock;
	Game game;

    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

		sf::Time dt = deltaClock.restart();
		float fDeltaTime = dt.asSeconds();
		
		Window.clear(sf::Color::Black);
        
		game.Draw(&Window);

		game.Update(fDeltaTime);

		Window.display();
    }

    return 0;
}