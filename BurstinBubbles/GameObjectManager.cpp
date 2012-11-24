#include "StdAfx.h"
#include "GameObjectManager.h"

GameObject player;

GameObjectManager::GameObjectManager(void)
{
	player = GameObject("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/player.png");
	Add(&player);
}


GameObjectManager::~GameObjectManager(void)
{
	for(std::vector<GameObject>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++ )
	{
		m_gameObjects.erase(i);
		break;
	}
}


void GameObjectManager::Update(float fDeltaTime)
{
	for(std::vector<GameObject>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		i->Update(fDeltaTime);
	}
}


void GameObjectManager::Draw(sf::RenderWindow *window)
{
	for(std::vector<GameObject>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		window->draw(*i);	
	}
}



void GameObjectManager::Remove(GameObject *gameObject)
{
	for(std::vector<GameObject>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++ )
	{
		if(gameObject == &(*i))
		{
			m_gameObjects.erase(i);
			break;
		}
	}
}


void GameObjectManager::Add(GameObject *gameObject)
{
	m_gameObjects.push_back(*gameObject);
}