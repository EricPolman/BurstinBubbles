#pragma once
#include "stdafx.h"

class Game
{
public:
	Game(void);
	~Game(void);
	void Update(float);
	void Draw(sf::RenderWindow*);

	//static int g_iWindowWidth;
	//static int g_iWindowHeight;
};

