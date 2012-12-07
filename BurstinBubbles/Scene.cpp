#include "StdAfx.h"
#include "Scene.h"
#include "TextureManager.h"

int Enemy::fCurrentEnemies;
int Enemy::fMAX_ACTIVE_ENEMIES;
int Enemy::fTOTAL_ENEMIES_PER_SCENE;
int Enemy::fSPAWNED_ENEMIES_PER_SCENE;

Scene::Scene(void)
{
	m_bScenePlaying = false;

	Enemy::fCurrentEnemies = 0;
	Enemy::fMAX_ACTIVE_ENEMIES = 12;
	Enemy::fTOTAL_ENEMIES_PER_SCENE = 50;
	Enemy::fSPAWNED_ENEMIES_PER_SCENE = 0;

	m_GameObjectManager = new GameObjectManager();
	m_font = new sf::Font();
	m_font->loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Fonts/defused.ttf");

	m_lifebarText.setString("Health");
	m_lifebarText.move(20,0);
	m_lifebarText.setFont(*m_font);
	m_lifebarText.setCharacterSize(16);
	m_lifebarText.setColor(sf::Color::Black);

	m_skull.setTexture(*TextureManager::getInstance()->m_Textures["skull"]);
	m_skull.setPosition(SCREEN_WIDTH - m_skull.getTextureRect().width - 10, SCREEN_HEIGHT - m_skull.getTextureRect().height - 40);

	std::string temp = "Starting";
	m_killText.setString(temp);

	m_killText.setPosition(SCREEN_WIDTH - m_skull.getTextureRect().width - 180, 0);
	m_killText.setFont(*m_font);
	m_killText.setCharacterSize(24);
	m_killText.setColor(sf::Color::Black);

	m_bCameraFollowsPlayer = true;
	m_bPlayerIsDead = false;

	m_lifeBar.setTexture(*TextureManager::getInstance()->m_Textures["lifebar"]);
	m_lifeBar.setPosition(20,20);
	m_lifeBar.setScale(1.0f,1);
	m_lifeBarRed.setTexture(*TextureManager::getInstance()->m_Textures["lifebarred"]);
	m_lifeBarRed.setPosition(20,20);
	m_lifeBarRed.setScale(1.0f,1);
	
	m_bScenePlaying = true;
}


Scene::~Scene(void)
{
	delete m_GameObjectManager;
}


void Scene::Update(float fDeltaTime)
{
	if(m_bScenePlaying)
	{
		m_GameObjectManager->Update(fDeltaTime);
		if(m_bCameraFollowsPlayer)
		{
			m_GameObjectManager->CenterPlayer();
		}
	}
	if(m_GameObjectManager->m_player->m_bIsDead || Enemy::fCurrentEnemies == 0)
	{
		m_bPlayerIsDead = true;
	}
}


void Scene::Draw(sf::RenderWindow *window)
{
	m_GameObjectManager->Draw(window);
	window->draw(m_lifeBarRed);
	m_lifeBar.setTextureRect(sf::IntRect(0,0, (m_GameObjectManager->m_player->m_fHealth / 100) * m_lifeBarRed.getTextureRect().width,m_lifeBarRed.getTextureRect().height));
	window->draw(m_lifeBar);
	window->draw(m_lifebarText);
	//window->draw(m_skull);
	int killText = Enemy::fCurrentEnemies + (Enemy::fTOTAL_ENEMIES_PER_SCENE - Enemy::fSPAWNED_ENEMIES_PER_SCENE);
	char temp[256];
	sprintf(temp, "%d enemies left", killText);
	m_killText.setString(temp);
	window->draw(m_killText);

}


void Scene::LoadFromFile(std::string sFile)
{
	/*
	 *	TODO: Implement loading of .scene-file. Placing assets, players, enemies, etc through GameObjectManager.
	 */
}