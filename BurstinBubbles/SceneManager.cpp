#include "StdAfx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextureManager.h"
#include "SoundManager.h"

float fRESTART_TIME = 5;
int pointCounter = 1;
int pointClock = 2;

SceneManager::SceneManager(void)
{
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/barrel.png", "barrel");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/player.png", "player");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/tree.png", "tree");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/bullet.png", "bullet");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/enemy.png", "enemy");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/loadingscreen.png", "loadingscreen");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/lifebar.png", "lifebar");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/lifebar_red.png", "lifebarred");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/medipack.png", "medipack");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/road_intersection.png", "road_intersection");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/road_vertical.png", "road_vertical");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/road_horizontal.png", "road_horizontal");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/field_grass.png", "field_grass");
	
	LoadSound(SettingHelper::g_sRootPath + "/Data/Sounds/shoot.wav", "shoot");
	LoadSound(SettingHelper::g_sRootPath + "/Data/Sounds/shoot_enemy.wav", "shoot_enemy");
	LoadSound(SettingHelper::g_sRootPath + "/Data/Sounds/impact_body.wav", "impact_body");
	LoadSound(SettingHelper::g_sRootPath + "/Data/Sounds/impact_body_player1.wav", "impact_body_player1");
	LoadSound(SettingHelper::g_sRootPath + "/Data/Sounds/impact_body_player2.wav", "impact_body_player2");
	LoadSound(SettingHelper::g_sRootPath + "/Data/Sounds/background_loading.wav", "background_loading", true);
	LoadSound(SettingHelper::g_sRootPath + "/Data/Sounds/background_scene1.wav", "background_scene1", true);
	
	LoadScene("Data\\Scenes\\default.scene");
	m_loadingText.setString("Loading...");
	m_loadingText.setColor(sf::Color::Black);
	m_loadingText.move(SettingHelper::g_iWindowWidth / 2 - 85, SettingHelper::g_iWindowHeight - 150);
	m_loadingText.setFont(*m_currentScene->m_font);
	m_loadingText.setCharacterSize(24);

	m_loadingScreen.setTexture(*TextureManager::getInstance()->m_Textures["loadingscreen"]);
	m_loadingScreen.setOrigin(m_loadingScreen.getTextureRect().width / 2,m_loadingScreen.getTextureRect().height / 2);
	m_loadingScreen.setPosition(SettingHelper::g_iWindowWidth / 2, SettingHelper::g_iWindowHeight / 2);
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
		pointClock++;
		if(pointClock % 240 == 0)
		{
			pointClock = 2;
			pointCounter++;
			if(pointCounter % 5 == 0)
			{
				pointCounter = 1;
			}
		}
		m_loadingText.setString("Loading");
		for(int i = 0; i < pointCounter - 1; i++)
		{
			m_loadingText.setString(m_loadingText.getString() + ".");
		}
		window->draw(m_loadingText);
	}
}