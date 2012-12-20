#include "StdAfx.h"
#include "Game.h"

float fTimer = 0;
float fTimerDraw = 0;
float fTIME = (1.0f / 60.0f);
float fDT = 0;

Game::Game(void)
{
	m_bIsStarted = false;
	m_bInstructionsOpen = false;
	m_font = new sf::Font();
	m_font->loadFromFile(SettingHelper::g_sRootPath + "/Data/Fonts/defused.ttf");
	
	menuView = new MenuView();
	GUIButton* startGame = new GUIButton();
	startGame->move(SettingHelper::g_iWindowWidth / 2, SettingHelper::g_iWindowHeight / 2 + 120);
	menuView->Add(startGame);
	m_textStartGame.setString("Start Game");
	m_textStartGame.setFont(*m_font);
	m_textStartGame.setCharacterSize(24);
	m_textStartGame.move(SettingHelper::g_iWindowWidth / 2 - m_textStartGame.getGlobalBounds().width / 2, 
					SettingHelper::g_iWindowHeight / 2 + 120 - m_textStartGame.getGlobalBounds().height / 2);

	GUIButton* instructions = new GUIButton();
	instructions->move(SettingHelper::g_iWindowWidth / 2, SettingHelper::g_iWindowHeight / 2 + 200);
	menuView->Add(instructions);
	m_textInstructions.setString("Instructions");
	m_textInstructions.setFont(*m_font);
	m_textInstructions.setCharacterSize(24);
	m_textInstructions.move(SettingHelper::g_iWindowWidth / 2 - m_textInstructions.getGlobalBounds().width / 2, 
					SettingHelper::g_iWindowHeight / 2 + 197 - m_textInstructions.getGlobalBounds().height / 2);

	GUIButton* exit = new GUIButton();
	exit->move(SettingHelper::g_iWindowWidth / 2, SettingHelper::g_iWindowHeight / 2 + 280);
	menuView->Add(exit);
	m_textExit.setString("Exit");
	m_textExit.setFont(*m_font);
	m_textExit.setCharacterSize(24);
	m_textExit.move(SettingHelper::g_iWindowWidth / 2 - m_textExit.getGlobalBounds().width / 2, 
					SettingHelper::g_iWindowHeight / 2 + 275 - m_textExit.getGlobalBounds().height / 2);
	
	GUIMuteButton* mute = new GUIMuteButton();
	mute->setPosition(SettingHelper::g_iWindowWidth - 100, SettingHelper::g_iWindowHeight - 100);
	menuView->Add(mute);
	
	menuView->LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/loadingscreen.png", "loadingscreen");
	m_beginImage.setTexture(*TextureManager::getInstance()->m_Textures["loadingscreen"]);
	
	menuView->LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/mute/music_on.png", "music_on");
	menuView->LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/mute/music_off.png", "music_off");
	menuView->LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/mute/music_hover.png", "music_hover");
	

	menuView->LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/instructions.png", "instructions");
	m_instrImage.setTexture(*TextureManager::getInstance()->m_Textures["instructions"]);
	m_instrImage.move(SettingHelper::g_iWindowWidth / 2 - m_instrImage.getTextureRect().width / 2,
		SettingHelper::g_iWindowHeight / 2 - m_instrImage.getTextureRect().height / 2);
	
	sceneManager = new SceneManager();
}


Game::~Game(void)
{
	delete sceneManager;
	delete menuView;
}


void Game::Update(float fDeltaTime)
{
	fTimer += fDeltaTime;
	fDT = fDeltaTime;
	if(fTimer > fTIME)
	{
		if(!m_bIsStarted)
		{
			menuView->Update(fTimer, sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
		}
		else
		{
			sceneManager->Update(fTimer);
		}
		fTimer = 0;
	}
}


void Game::Draw(sf::RenderWindow* window)
{
	window->draw(m_beginImage);
	if(!m_bIsStarted)
	{
		menuView->Draw(window);
		window->draw(m_textExit);
		window->draw(m_textStartGame);
		window->draw(m_textInstructions);
		if(!m_bInstructionsOpen)
		{
			if(menuView->m_guiButtons[0]->m_bOldMouseClick && !menuView->m_guiButtons[0]->m_bMouseClick && menuView->m_guiButtons[0]->intersectsRect(sf::Mouse::getPosition()))
			{
				m_bIsStarted = true;
				if(!(SoundManager::getInstance()->m_sounds["background_scene1"]->getStatus() == sf::Sound::Playing))
				{
					SoundManager::getInstance()->m_sounds["background_loading"]->stop();
					SoundManager::getInstance()->PlayMusic("background_scene1");
				}
			}
			else if(menuView->m_guiButtons[1]->m_bOldMouseClick && !menuView->m_guiButtons[1]->m_bMouseClick && menuView->m_guiButtons[1]->intersectsRect(sf::Mouse::getPosition()))
			{
				m_bInstructionsOpen = true;
			}
			else if(menuView->m_guiButtons[2]->m_bOldMouseClick && !menuView->m_guiButtons[2]->m_bMouseClick && menuView->m_guiButtons[2]->intersectsRect(sf::Mouse::getPosition()))
			{
				window->close();
			}
			else if(menuView->m_guiButtons[3]->m_bOldMouseClick && !menuView->m_guiButtons[3]->m_bMouseClick && menuView->m_guiButtons[3]->intersectsRect(sf::Mouse::getPosition()))
			{
				bool mute = ((GUIMuteButton*)menuView->m_guiButtons[3])->mute;
				if(mute)
				{
					((GUIMuteButton*)menuView->m_guiButtons[3])->mute = false;
					SoundManager::getInstance()->m_sounds["background_loading"]->setVolume(100);
					SoundManager::getInstance()->m_sounds["background_scene1"]->setVolume(100);
				}
				else
				{
					((GUIMuteButton*)menuView->m_guiButtons[3])->mute = true;
					SoundManager::getInstance()->m_sounds["background_loading"]->setVolume(0);
					SoundManager::getInstance()->m_sounds["background_scene1"]->setVolume(0);
				}
			}
		}	
		else
		{
			window->draw(m_instrImage);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				m_bInstructionsOpen = false;
			}
		}
	}
	else
	{
		sceneManager->Draw(window);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			m_bIsStarted = false;
			m_textStartGame.setString("Continue");
			m_textStartGame.setPosition(SettingHelper::g_iWindowWidth / 2 - m_textStartGame.getGlobalBounds().width / 2, 
					SettingHelper::g_iWindowHeight / 2 + 120 - m_textStartGame.getGlobalBounds().height / 2);

			SoundManager::getInstance()->m_sounds["background_scene1"]->stop();
			SoundManager::getInstance()->PlayMusic("background_loading");
		}
	}	
}