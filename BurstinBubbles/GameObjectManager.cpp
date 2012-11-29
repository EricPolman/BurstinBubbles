#include "StdAfx.h"
#include "GameObjectManager.h"
#include "Game.h"


GameObjectManager::GameObjectManager(void)
{
	Add(&GameObject("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/testing_ground.png")); 
	AddPlayer(&Player("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/player.png"));
	
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


	for(std::vector<Player>::iterator i = m_Players.begin(); i != m_Players.end(); ++i )
	{
		i->Update(fDeltaTime);
	}
	//player.Update(fDeltaTime);
}

void GameObjectManager::CenterPlayer(void)
{
	sf::Vector2f center(500,300);
	sf::Vector2f translation = center - m_Players[0].getPosition();

	for(std::vector<GameObject>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		i->move(translation);
	}


	for(std::vector<Player>::iterator i = m_Players.begin(); i != m_Players.end(); ++i )
	{
		i->setPosition(center);
	}
}


void GameObjectManager::Draw(sf::RenderWindow *window)
{
	//window->draw(player);
	for(std::vector<GameObject>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		window->draw(*i);	
	}
	
	for(std::vector<Player>::iterator i = m_Players.begin(); i != m_Players.end(); ++i )
	{
		window->draw(*i);
		//std::cout << i->getTextureRect().width;
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


void GameObjectManager::AddPlayer(Player *player)
{
	m_Players.push_back(*player);
}