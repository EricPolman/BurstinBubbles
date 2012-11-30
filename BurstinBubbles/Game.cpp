#include "StdAfx.h"
#include "Game.h"
#include "SceneManager.h"


SceneManager sceneManager;
float fTimer = 0;
float fTimerDraw = 0;
float fTIME = (1.0f / 60.0f);
float fDT = 0;


Game::Game(void)
{
	//g_iWindowWidth = 100;
	//g_iWindowHeight = 100;
}


Game::~Game(void)
{
}


void Game::Update(float fDeltaTime)
{
	fTimer += fDeltaTime;
	fDT = fDeltaTime;
	if(fTimer > fTIME)
	{
		sceneManager.Update(fTimer);
		//std::cout << fTimer << std::endl;
		fTimer = 0;
	}
}


void Game::Draw(sf::RenderWindow* window)
{
	//g_iWindowWidth = window->getSize().x;
	//g_iWindowHeight = window->getSize().y;

	sceneManager.Draw(window);
}