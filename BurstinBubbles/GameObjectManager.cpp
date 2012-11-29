#include "StdAfx.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Game.h"


GameObjectManager::GameObjectManager(void)
{
	sf::Texture tex1;
	tex1.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/testing_ground.png");
	TextureManager::getInstance()->m_Textures["testing_ground"] = tex1;
	Add(&GameObject("testing_ground")); 
	
	sf::Texture tex2;
	tex2.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/barrel.png");
	TextureManager::getInstance()->m_Textures["barrel"] = tex2;
	
	GameObject barrel("barrel");
	barrel.move(200,200);
	AddCollidable(&barrel);

	GameObject barrel2("barrel");
	barrel2.move(-200,200);
	AddCollidable(&barrel2);

	GameObject barrel3("barrel");
	barrel3.move(-200,-200);
	AddCollidable(&barrel3);

	GameObject barrel4("barrel");
	barrel4.move(200,-200);
	AddCollidable(&barrel4);

	sf::Texture tex3;
	tex3.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/player.png");
	TextureManager::getInstance()->m_Textures["player"] = tex3;
	
	AddPlayer(&Player("player"));

	sf::Texture tex4;
	tex4.loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/bullet.png");
	TextureManager::getInstance()->m_Textures["bullet"] = tex4;	
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

		for(std::vector<Bullet>::iterator k = i->m_bullets.begin(); k != i->m_bullets.end(); ++k )
		{
			AddPlayerBullet(&(*k));
		}
	}

	std::vector<std::vector<Bullet>::iterator> bulletsToBeRemoved;
	bulletsToBeRemoved.clear();
	for(std::vector<Bullet>::iterator i = m_PlayerBullets.begin(); i != m_PlayerBullets.end(); ++i )
	{
		i->Update(fDeltaTime);
		if(i->m_fBulletLifetime > 5)
		{
			bulletsToBeRemoved.push_back(i);
		}
	}
	for(std::vector<std::vector<Bullet>::iterator>::iterator i = bulletsToBeRemoved.begin(); i != bulletsToBeRemoved.end(); ++i)
	{
		m_PlayerBullets.erase(*i);
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
	for(std::vector<Bullet>::iterator i = m_PlayerBullets.begin(); i != m_PlayerBullets.end(); ++i )
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
	for(std::vector<Bullet>::iterator j = m_PlayerBullets.begin(); j != m_PlayerBullets.end(); ++j )
	{
		window->draw(*j);
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

void GameObjectManager::AddPlayerBullet(Bullet *bullet)
{
	m_PlayerBullets.push_back(*bullet);
}