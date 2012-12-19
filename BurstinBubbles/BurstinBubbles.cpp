#include "stdafx.h"
#include "Game.h"

int SettingHelper::g_iWindowWidth = 0;
int SettingHelper::g_iWindowHeight = 0;

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_HIDE );
	SettingHelper::GetRootPath();
	sf::RenderWindow Window(sf::VideoMode::getFullscreenModes()[0], "Burstin' Bubbles", sf::Style::Fullscreen);
    sf::Clock deltaClock;
	SettingHelper::g_iWindowWidth = Window.getSize().x;
	SettingHelper::g_iWindowHeight = Window.getSize().y;
    
	Game game;
	
    while (Window.isOpen())
    {	
		sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();

			if (event.type == sf::Event::Resized)
			{
				SettingHelper::g_iWindowWidth = Window.getSize().x;
				SettingHelper::g_iWindowHeight = Window.getSize().y;
			}
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