#include "StdAfx.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "Enemy.h"


GameObjectManager::GameObjectManager(void)
{
	m_gameObjects.clear();
	m_gameObjects.reserve(200);
	GameObject* testingGrounds = new GameObject("testing_ground");
	testingGrounds->m_bIsCollidable = false;
	Add(testingGrounds); 
	
	
	for(int i = 0; i < 6; i++)
	{
		GameObject* barrel = new GameObject("barrel");
		
		barrel->move(-300 + i * 100.0f, -50);
		Add(barrel);
	}
	for(int i = 0; i < 6; i++)
	{
		GameObject* tree = new GameObject("tree");
		
		tree->move(-150 - 150 * i, 110);
		Add(tree);
	}
	for(int i = 0; i < 5; i++)
	{
		GameObject* tree = new GameObject("tree");
		
		tree->move(-150, 110 + 150 + 150 * i);
		Add(tree);
	}
	GameObject* pond = new GameObject("pond");
	pond->move(-400, 400);
	Add(pond);
	
	Player* player = new Player("player");
	Add(player);
	m_player = player; 
	Enemy::g_player = player;

	GameObject* square = new GameObject("square", false);
	square->move(0,-300);
	Add(square);
	
	for(int i = 0; i < Enemy::fMAX_ACTIVE_ENEMIES / 2; i++)
	{
		Enemy* enemy = new Enemy();
		float degree = ((360/ Enemy::fMAX_ACTIVE_ENEMIES / 2) * i) * PI / 180;
		sf::Vector2f newPos(cos(degree), sin(degree));

		enemy->move(newPos * 800.0f);
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
	m_gameObjects.clear();
}


void GameObjectManager::Update(float fDeltaTime)
{
	if(Enemy::fCurrentEnemies < Enemy::fMAX_ACTIVE_ENEMIES && Enemy::fSPAWNED_ENEMIES_PER_SCENE < Enemy::fTOTAL_ENEMIES_PER_SCENE)
	{
		Enemy* enem = new Enemy();
		enem->move(-200,-200);
		Add(enem);
	}

	for(std::vector<GameObject*>::iterator j = m_gameObjects.begin(); j != m_gameObjects.end(); ++j )
	{
		if((*j) != NULL)
		{
			for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
			{
				if((*i) != NULL)
				{
					if((*j)->m_bIsCollidable && (*i)->m_bIsCollidable && (*i)->m_collider->Intersects((*j)->m_collider) && *i != *j)
					{
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
	for(std::vector<Bullet*>::iterator k = m_player->m_bullets.begin(); k != m_player->m_bullets.end(); ++k )
	{
		if((*k) != NULL)
			Add(*k);
	}
	m_player->m_bullets.clear();

	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		(*i)->Update(fDeltaTime);
		if((*i)->m_bIsDead)
		{
			(*i)->Die();
			m_gameObjects.erase(i--);
		}
	}
}

void GameObjectManager::CenterPlayer(void)
{
	sf::Vector2f center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
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