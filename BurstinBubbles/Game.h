#pragma once
#include "stdafx.h"
#include "SceneManager.h"
#include "MenuView.h"

class Game
{
public:
	Game(void);
	~Game(void);
	void Update(float);
	void Draw(sf::RenderWindow*);
	
	sf::Sprite m_instrImage;
	sf::Sprite m_beginImage;
	sf::Text m_textStartGame;
	sf::Text m_textInstructions;
	sf::Text m_textExit;
	sf::Font* m_font;

	SceneManager* sceneManager;
	MenuView* menuView;
	bool m_bIsStarted;
	bool m_bInstructionsOpen;
};

