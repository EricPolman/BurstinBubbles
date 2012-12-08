#include "StdAfx.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "Enemy.h"
#include "Medipack.h"

GameObjectManager::GameObjectManager(void)
{
	m_gameObjects.clear();
	m_gameObjects.reserve(200);
	GameObject* testingGrounds = new GameObject("testing_ground");
	testingGrounds->m_bIsCollidable = false;
	//Add(testingGrounds); 
	
	for(int i = 0; i < 6; i++)
	{
		GameObject* barrel = new GameObject("barrel");
		
		barrel->move(100 + i * 100.0f, -30 + (i%2 * 100));
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

	for(int i = 0; i < 10; i++)
	{
		Medipack* medipack = new Medipack();
		float x = -2000 + MathHelper::Random() * 4000.0f;
		float y = -2000 + MathHelper::Random() * 4000.0f;

		medipack->move(x, y);
		Add(medipack);
	}

	for(int i = 0; i < 20; i++)
	{
		GameObject* tree = new GameObject("tree");
		tree->move(-1000.0f + MathHelper::Random() * 500.0f, 200.0f + MathHelper::Random() * 600.0f);
		Add(tree);
	}
	for(int i = 0; i < 20; i++)
	{
		GameObject* tree = new GameObject("tree");
		tree->move(765.0f + MathHelper::Random() * 470.0f, -820.0f + MathHelper::Random() * 740.0f);
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
	square->move(-50,-320);
	Add(square);
	square = new GameObject("square", false);
	square->move(350,-320);
	Add(square);
	square = new GameObject("square", false);
	square->move(350,370);
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