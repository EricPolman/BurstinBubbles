#include "StdAfx.h"
#include "Game.h"
#include "SceneManager.h"

SceneManager sceneManager;
float fTimer = 0;
float fTIME = (1.0f / 60.0f);

Game::Game(void)
{
}


Game::~Game(void)
{
}


void Game::Update(float fDeltaTime)
{
	fTimer += fDeltaTime;
	if(fTimer > fTIME)
	{
		sceneManager.Update(fTimer);
		fTimer -= fTIME;
	}
}