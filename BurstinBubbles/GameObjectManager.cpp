#include "StdAfx.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "Enemy.h"

GameObjectManager::GameObjectManager(void)
{
	m_gameObjects.clear();
	m_gameObjects.reserve(200);
	
	Player* player = new Player("player");
	Add(player);
	m_player = player; 
	Enemy::g_player = player;

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
		float f = MathHelper::Random();
		int moveX = 0, moveY = 0;
		if(f < 0.25f)
		{
			moveX = SCREEN_WIDTH + 200;
			moveY = SCREEN_HEIGHT + 200;
		}
		else if(f > 0.25f && f <= 0.5f)
		{
			moveX = SCREEN_WIDTH + 200;
			moveY = -200;
		}
		else if(f > 0.5f && f <= 0.75f)
		{
			moveX = -200;
			moveY = SCREEN_HEIGHT + 200;
		}
		else if(f > 0.75f)
		{
			moveX = -200;
			moveY = -200;
		}
		enem->move(moveX, moveY);
		Add(enem);
	}

	for(std::vector<GameObject*>::iterator j = m_gameObjects.begin(); j != m_gameObjects.end(); ++j )
	{
		if((*j) != NULL && (*j)->getPosition().x > -100 && (*j)->getPosition().y > -100 && (*j)->getPosition().x < SCREEN_WIDTH+100 && (*j)->getPosition().y < SCREEN_HEIGHT+100)
		{
			for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
			{
				if((*i) != NULL && (*i)->getPosition().x > -100 && (*i)->getPosition().y > -100 && (*i)->getPosition().x < SCREEN_WIDTH+100 && (*i)->getPosition().y < SCREEN_HEIGHT+100)
				{
					if((*j)->m_bIsCollidable && (*i)->m_bIsCollidable && (*i)->m_collider->Intersects((*j)->m_collider) && *i != *j)
					{
						(*i)->Hit(*j);
					}
				}
			}
		}
	}

	Enemy::fCurrentEnemies = 0;
	for(std::vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i )
	{
		if((*i)->GetType() == "Enemy")
		{
			if(!(*i)->m_bIsDead)
			{
				Enemy::fCurrentEnemies++;
			}
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
		if(!(*i)->m_bIsDead  && (*i)->getPosition().x > -200 && (*i)->getPosition().y > -200 && (*i)->getPosition().x < SCREEN_WIDTH+200 && (*i)->getPosition().y < SCREEN_HEIGHT+200)
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