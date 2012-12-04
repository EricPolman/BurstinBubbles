#include "StdAfx.h"
#include "Scene.h"
#include "TextureManager.h"


Scene::Scene(void)
{
	m_bScenePlaying = false;
	m_GameObjectManager = new GameObjectManager();
	
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
	if(m_GameObjectManager->m_player->m_bIsDead)
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
}


void Scene::LoadFromFile(std::string sFile)
{
	/*
	 *	TODO: Implement loading of .scene-file. Placing assets, players, enemies, etc through GameObjectManager.
	 */
}