#pragma once
#include "SFML/Graphics.hpp"

class Game
{
public:
	Game(void);
	~Game(void);
	void Update(float);
	void Draw(sf::RenderWindow*);
};

