#include "StdAfx.h"
#include "Enemy.h"
#include "Bullet.h"

Player* Enemy::g_player;


Enemy::Enemy(void) : GameObject("enemy")
{

}


Enemy::~Enemy(void)
{
}


void Enemy::Hit(GameObject* other)
{
	if(!other->m_bIsDead)
	{
		if(other->GetType() == "Bullet")
		{
			if(((Bullet*)(other))->m_owner->GetType() != "Enemy")
			{
				m_fHealth -= 10;
			}
		}
	}
}


void Enemy::Update(float fDeltaTime)
{
	
	sf::Vector2f dir(sf::Vector2f(g_player->getPosition().x,g_player->getPosition().y) - getPosition());
	float mag = Distance(sf::Vector2f(g_player->getPosition().x,g_player->getPosition().y), getPosition());
	dir.x /= mag;
	dir.y /= mag;
	float newRot = asinf(dir.x) * 180 / PI;
	if(dir.y >0)
	{	
		newRot = 180 - newRot;
	}
	setRotation(newRot);

	if(m_fHealth < 1)
	{
		m_bIsDead = true;
	}
}


std::string Enemy::GetType(void)
{
	return "Enemy";
}