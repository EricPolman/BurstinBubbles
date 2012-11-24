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
		fTimer -= fTIME;
	}
}


void Game::Draw(sf::RenderWindow* window)
{
	sceneManager.Draw(window);
}