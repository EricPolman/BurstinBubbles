#include "StdAfx.h"
#include "Enemy.h"
#include "Bullet.h"

Player* Enemy::g_player;
float fSHOOT_TIME = 1.0f;

Enemy::Enemy(void) : GameObject("enemy")
{

}


Enemy::Enemy(const Enemy& enemy) : GameObject("enemy")
{
	m_bullets = enemy.m_bullets;
}


Enemy::~Enemy(void)
{
}


void Enemy::Update(float fDeltaTime)
{
	sf::Vector2f dir(sf::Vector2f(g_player->getPosition().x,g_player->getPosition().y) - getPosition());
	dir = NormalizeVector(dir);
	float newRot = asinf(dir.x) * 180 / PI;
	if(dir.y >0)
	{	
		newRot = 180 - newRot;
	}
	setRotation(newRot);

	m_fShootTimer += fDeltaTime;
	if(Distance(g_player->getPosition(), getPosition()) > 300)
	{
		move(NormalizeVector(g_player->getPosition() - getPosition()) * m_fMaximumSpeed * fDeltaTime);
	}
	else
	{
		if(Distance(g_player->getPosition(), getPosition()) > 100 && Distance(g_player->getPosition(), getPosition()) < 350)
		{
			if(m_fShootTimer > fSHOOT_TIME)
			{
				m_fShootTimer = 0;
				Shoot();
			}
		}
		else
		{
			move(NormalizeVector(getPosition() - g_player->getPosition()) * m_fMaximumSpeed * 0.5f * fDeltaTime);
		}
	}

	if(m_fHealth < 1)
	{
		m_bIsDead = true;
	}
}


void Enemy::Hit(GameObject* other)
{
	if(!other->m_bIsDead)
	{
		sf::Vector2f normalizedDir = getPosition() - other->getPosition();
		float dist = Distance(getPosition(), other->getPosition());
		normalizedDir = NormalizeVector(normalizedDir);

		move(normalizedDir * ((getTextureRect().width + other->getTextureRect().width) / 2 - dist) * 0.5f);

		if(other->GetType() == "Bullet")
		{
			if(((Bullet*)(other))->m_owner != this)
			{
				m_fHealth -= 10;
			}
		}
	}
}


void Enemy::Shoot(void)
{
	Bullet* bullet = new Bullet();
	bullet->m_direction = sf::Vector2f(std::cos(PI * (getRotation() - 90) / 180.0f), std::sin(PI * (getRotation() - 90) / 180.0f));
	bullet->setPosition(getPosition() + bullet->m_direction * (float)(getTextureRect().width / 2));
	bullet->m_owner = this;
	m_bullets.push_back(bullet);
}


std::string Enemy::GetType(void)
{
	return "Enemy";
}