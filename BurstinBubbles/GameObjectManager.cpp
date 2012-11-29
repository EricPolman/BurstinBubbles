#include "StdAfx.h"
#include "GameObjectManager.h"
#include "Game.h"


GameObjectManager::GameObjectManager(void)
{
	Add(&GameObject("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/testing_ground.png")); 
	
	GameObject barrel("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png");
	barrel.move(200,200);
	AddCollidable(&barrel);

	GameObject barrel2("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png");
	barrel2.move(-200,200);
	AddCollidable(&barrel2);

	GameObject barrel3("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png");
	barrel3.move(-200,-200);
	AddCollidable(&barrel3);

	GameObject barrel4("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png");
	barrel4.move(200,-200);
	AddCollidable(&barrel4);

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
	for(std::vector<GameObject>::iterator i = m_collidableGameObjects.begin(); i != m_collidableGameObjects.end(); ++i )
	{
		i->Update(fDeltaTime);
	}

	for(std::vector<Player>::iterator i = m_Players.begin(); i != m_Players.end(); ++i )
	{
		for(std::vector<GameObject>::iterator j = m_collidableGameObjects.begin(); j != m_collidableGameObjects.end(); ++j )
		{
			if(i->isColliding(&(*j)))
			{
				sf::Vector2f normalizedDir = i->getPosition() - j->getPosition();
				float dist = i->Distance(i->getPosition(), j->getPosition());
				normalizedDir.x /= dist;
				normalizedDir.y /= dist;

				i->move(normalizedDir * ((i->getTextureRect().width + j->getTextureRect().width) / 2 - dist));
			}
		}
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
	for(std::vector<GameObject>::iterator i = m_collidableGameObjects.begin(); i != m_collidableGameObjects.end(); ++i )
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
	for(std::vector<GameObject>::iterator i = m_collidableGameObjects.begin(); i != m_collidableGameObjects.end(); ++i )
	{
		window->draw(*i);	
	}
	
	for(std::vector<Player>::iterator i = m_Players.begin(); i != m_Players.end(); ++i )
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

void GameObjectManager::AddCollidable(GameObject *gameObject)
{
	m_collidableGameObjects.push_back(*gameObject);
}

void GameObjectManager::AddPlayer(Player *player)
{
	m_Players.push_back(*player);
}