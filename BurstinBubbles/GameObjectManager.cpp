#include "StdAfx.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Game.h"


GameObjectManager::GameObjectManager(void)
{
	sf::Texture tex1;
	tex1.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/testing_ground.png");
	TextureManager::getInstance()->m_Textures["testing_ground"] = tex1;
	GameObject* testingGrounds = new GameObject("testing_ground");
	testingGrounds->m_bIsCollidable = false;
	Add(testingGrounds); 
	
	sf::Texture tex2;
	tex2.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png");
	TextureManager::getInstance()->m_Textures["barrel"] = tex2;
	
	GameObject* barrel = new GameObject("barrel");
	barrel->move(200,200);
	Add(barrel);

	GameObject* barrel2 = new GameObject("barrel");
	barrel2->move(-200,200);
	Add(barrel2);

	GameObject* barrel3 = new GameObject("barrel");
	barrel3->move(-200,-200);
	Add(barrel3);

	GameObject* barrel4 = new GameObject("barrel");
	barrel4->move(200,-200);
	Add(barrel4);

	sf::Texture tex3;
	tex3.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/player.png");
	TextureManager::getInstance()->m_Textures["player"] = tex3;
	
	Player* player = new Player("player");
	Add(player);
	m_player = player; 

	sf::Texture tex4;
	tex4.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/bullet.png");
	TextureManager::getInstance()->m_Textures["bullet"] = tex4;
}


GameObjectManager::~GameObjectManager(void)
{
}


void GameObjectManager::Update(float fDeltaTime)
{
	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		(*i)->Update(fDeltaTime);
	}
	
	for(std::vector<GameObject*>::iterator j = m_gameObjects.begin(); j != m_gameObjects.end(); ++j )
	{
		for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
		{
			if((*j)->m_bIsCollidable && (*i)->m_bIsCollidable && (*i)->isColliding(*j) && *i != *j)
			{
				(*j)->Hit(*i);
				(*i)->Hit(*j);
			}
		}
	}

	for(std::vector<Bullet*>::iterator k = m_player->m_bullets.begin(); k != m_player->m_bullets.end(); ++k )
	{
		Add(*k);
	}

	std::vector<std::vector<GameObject*>::iterator> objectsToBeRemoved;
	objectsToBeRemoved.clear();
	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		(*i)->Update(fDeltaTime);
		if((*i)->m_bIsDead)
		{
			objectsToBeRemoved.push_back(i);
		}
	}
	for(std::vector<std::vector<GameObject*>::iterator>::iterator i = objectsToBeRemoved.begin(); i != objectsToBeRemoved.end(); ++i)
	{
		m_gameObjects.erase(*i);
	}
}

void GameObjectManager::CenterPlayer(void)
{
	sf::Vector2f center(500,300);
	sf::Vector2f translation = center - m_player->getPosition();

	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		if(m_player != *i)
			(*i)->move(translation);
	}

	m_player->setPosition(center);
}


void GameObjectManager::Draw(sf::RenderWindow *window)
{
	//window->draw(player);
	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		window->draw(*(*i));	
	}	
}


void GameObjectManager::Remove(GameObject *gameObject)
{
	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++ )
	{
		if(gameObject == *i)
		{
			m_gameObjects.erase(i);
			break;
		}
	}
}


void GameObjectManager::Add(GameObject *gameObject)
{
	m_gameObjects.push_back(gameObject);
}