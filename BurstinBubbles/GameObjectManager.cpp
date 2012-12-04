#include "StdAfx.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "Enemy.h"


GameObjectManager::GameObjectManager(void)
{
	m_gameObjects.reserve(200);
	sf::Texture tex1;
	tex1.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/testing_ground.png");
	TextureManager::getInstance()->m_Textures["testing_ground"] = tex1;
	GameObject* testingGrounds = new GameObject("testing_ground");
	testingGrounds->m_bIsCollidable = false;
	Add(testingGrounds); 
	
	sf::Texture tex2;
	tex2.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png");
	TextureManager::getInstance()->m_Textures["barrel"] = tex2;
	
	for(int i = 0; i < 6; i++)
	{
		GameObject* barrel = new GameObject("barrel");
		float degree = (60 * i) * PI / 180;
		sf::Vector2f newPos(cos(degree), sin(degree));
		
		barrel->move(newPos * 100.0f);
		Add(barrel);
	}

	sf::Texture tex3;
	tex3.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/player.png");
	TextureManager::getInstance()->m_Textures["player"] = tex3;
	
	Player* player = new Player("player");
	Add(player);
	m_player = player; 
	Enemy::g_player = player;

	sf::Texture tex4;
	tex4.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/bullet.png");
	TextureManager::getInstance()->m_Textures["bullet"] = tex4;

	sf::Texture tex5;
	tex5.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/enemy.png");
	TextureManager::getInstance()->m_Textures["enemy"] = tex5;
	
	for(int i = 0; i < 20; i++)
	{
		Enemy* enemy = new Enemy();
		float degree = (18 * i) * PI / 180;
		sf::Vector2f newPos(cos(degree), sin(degree));

		enemy->move(newPos * 400.0f);
		Add(enemy);
	}
}


GameObjectManager::GameObjectManager(const GameObjectManager& other)
{
	m_gameObjects = other.m_gameObjects;
	m_gameObjects.reserve(other.m_gameObjects.size() * 2);
	m_player = other.m_player;
}


GameObjectManager::~GameObjectManager(void)
{
	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		delete *i;
	}
}


void GameObjectManager::Update(float fDeltaTime)
{
	for(std::vector<GameObject*>::iterator j = m_gameObjects.begin(); j != m_gameObjects.end(); ++j )
	{
		if((*j) != NULL)
		{
			for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
			{
				if((*i) != NULL)
				{
					if((*j)->m_bIsCollidable && (*i)->m_bIsCollidable && (*i)->isColliding(*j) && *i != *j)
					{
						(*j)->Hit(*i);
						(*i)->Hit(*j);
					}
				}
			}
		}
	}

	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		if((*i)->GetType() == "Enemy")
		{
			for(std::vector<Bullet*>::iterator k = ((Enemy*)(*i))->m_bullets.begin(); k != ((Enemy*)(*i))->m_bullets.end(); ++k )
			{
				if((*k) != NULL)
					Add((GameObject*)*k);
			}
			((Enemy*)(*i))->m_bullets.clear();
		}
	}
	std::cout << std::endl;
	for(std::vector<Bullet*>::iterator k = m_player->m_bullets.begin(); k != m_player->m_bullets.end(); ++k )
	{
		if((*k) != NULL)
			Add(*k);
	}
	m_player->m_bullets.clear();

	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		(*i)->Update(fDeltaTime);
		if((*i)->GetType() == "Enemy")
		{
			//((Enemy*)(*i))->m_bullets.clear();
		}
		if((*i)->m_bIsDead)
		{
			m_gameObjects.erase(i--);
		}
	}
}

void GameObjectManager::CenterPlayer(void)
{
	sf::Vector2f center(500,300);
	sf::Vector2f translation = center - m_player->getPosition();

	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		if(*i != NULL && m_player != *i)
			(*i)->move(translation);
	}

	m_player->setPosition(center);
}


void GameObjectManager::Draw(sf::RenderWindow *window)
{
	m_player->UpdateMouse(*window);

	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		if(!(*i)->m_bIsDead)
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