#include "StdAfx.h"
#include "SceneManager.h"
#include "Scene.h"
#include <direct.h>
#include "TextureManager.h"
#include "SoundManager.h"

float fRESTART_TIME = 5;

SceneManager::SceneManager(void)
{
	char CurrentPath[_MAX_PATH];
    _getcwd(CurrentPath, _MAX_PATH);
	g_sRootPath = CurrentPath;

	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png", "barrel");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/player.png", "player");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/tree.png", "tree");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/bullet.png", "bullet");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/enemy.png", "enemy");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/loadingscreen.png", "loadingscreen");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/lifebar.png", "lifebar");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/lifebar_red.png", "lifebarred");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/pond.png", "pond");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/square.png", "square");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/medipack.png", "medipack");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/road_intersection.png", "road_intersection");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/road_vertical.png", "road_vertical");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/road_horizontal.png", "road_horizontal");
	LoadTexture("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/field_grass.png", "field_grass");
	
	LoadSound("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sounds/shoot.wav", "shoot");
	LoadSound("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sounds/shoot_enemy.wav", "shoot_enemy");
	LoadSound("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sounds/impact_body.wav", "impact_body");
	LoadSound("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sounds/impact_body_player1.wav", "impact_body_player1");
	LoadSound("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sounds/impact_body_player2.wav", "impact_body_player2");
	LoadSound("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sounds/background_loading.wav", "background_loading", true);
	LoadSound("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sounds/background_scene1.wav", "background_scene1", true);
	
	LoadScene("Data\\Scenes\\default.scene");

	
	m_loadingScreen.setTexture(*TextureManager::getInstance()->m_Textures["loadingscreen"]);
	m_loadingScreen.setOrigin(m_loadingScreen.getTextureRect().width / 2,m_loadingScreen.getTextureRect().height / 2);
	m_loadingScreen.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}


SceneManager::~SceneManager(void)
{
	delete m_currentScene;
}


void SceneManager::LoadTexture(std::string path, std::string name)
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile(path);
	TextureManager::getInstance()->m_Textures[name] = tex;
}


void SceneManager::LoadSound(std::string path, std::string name, bool loop)
{
	SoundManager::getInstance()->Add(name, path, loop);
}


void SceneManager::Update(float fDeltaTime)
{
	m_currentScene->Update(fDeltaTime);
	if(m_currentScene->m_bPlayerIsDead)
	{
		delete m_currentScene;
		LoadScene("");
		//m_currentScene->LoadFromFile(g_sRootPath + "\\" + "Data\\Scenes\\default.scene");
	}
	if(!m_currentScene->m_bScenePlaying)
	{
		m_fSceneRestartTimer += fDeltaTime;
		if(m_fSceneRestartTimer > fRESTART_TIME)
		{
			m_currentScene->m_bScenePlaying = true;
			SoundManager::getInstance()->m_sounds["background_loading"]->stop();
			SoundManager::getInstance()->Play("background_scene1");
		}
	}
}


void SceneManager::LoadScene(std::string sFile)
{
	m_currentScene = new Scene();
	SoundManager::getInstance()->m_sounds["background_scene1"]->stop();
	SoundManager::getInstance()->Play("background_loading");
	m_fSceneRestartTimer = 0;
	m_currentScene->m_bScenePlaying = false;
	//m_currentScene->LoadFromFile(g_sRootPath + "\\" + sFile);
}


void SceneManager::UnloadScene(void)
{
}


void SceneManager::Draw(sf::RenderWindow *window)
{
	if(m_currentScene->m_bScenePlaying)
	{
		m_currentScene->Draw(window);
	}
	else
	{
		window->draw(m_loadingScreen);
	}
}