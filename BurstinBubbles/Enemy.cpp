#include "StdAfx.h"
#include "Enemy.h"
#include "Bullet.h"

Player* Enemy::g_player;
float fSHOOT_TIME = 0.8f;

float Enemy::fCurrentEnemies = 0;
float Enemy::fMAX_ACTIVE_ENEMIES = 15;
float Enemy::fTOTAL_ENEMIES_PER_SCENE = 50;
float Enemy::fSPAWNED_ENEMIES_PER_SCENE = 0;

Enemy::Enemy(void) : GameObject("enemy")
{
	Enemy::fCurrentEnemies++;
	Enemy::fSPAWNED_ENEMIES_PER_SCENE++;
	delete m_collider;
	m_collider = new Collider(&(getPosition()), getTextureRect().width / 2.0f);
}


Enemy::Enemy(const Enemy& enemy) : GameObject("enemy")
{
	m_bullets = enemy.m_bullets;
	delete m_collider;
	m_collider = new Collider(&(getPosition()), getTextureRect().width / 2.0f);
}


Enemy::~Enemy(void)
{
}


void Enemy::Die(void)
{
	Enemy::fCurrentEnemies--;
	std::cout << fCurrentEnemies << " enemies left." << std::endl;
}


void Enemy::Update(float fDeltaTime)
{
	sf::Vector2f dir(sf::Vector2f(g_player->getPosition().x,g_player->getPosition().y) - getPosition());
	dir = MathHelper::Normalize(dir);
	float newRot = asinf(dir.x) * 180 / PI;
	if(dir.y >0)
	{	
		newRot = 180 - newRot;
	}
	setRotation(newRot);

	m_fShootTimer += fDeltaTime;
	if(MathHelper::Distance(g_player->getPosition(), getPosition()) > 300)
	{
		move(MathHelper::Normalize(g_player->getPosition() - getPosition()) * m_fMaximumSpeed * fDeltaTime);
	}
	else
	{
		if(MathHelper::Distance(g_player->getPosition(), getPosition()) > 100 && MathHelper::Distance(g_player->getPosition(), getPosition()) < 350)
		{
			if(m_fShootTimer > fSHOOT_TIME)
			{
				m_fShootTimer = 0;
				Shoot();
			}
		}
		else
		{
			move(MathHelper::Normalize(getPosition() - g_player->getPosition()) * m_fMaximumSpeed * 0.5f * fDeltaTime);
		}
	}

	if(m_fHealth < 1)
	{
		m_bIsDead = true;
	}
}


void Enemy::Hit(GameObject* other)
{
	if(other->m_collider->IsCircular)
	{
		sf::Vector2f normalizedDir = getPosition() - other->getPosition();
		float dist = MathHelper::Distance(getPosition(), other->getPosition());
		normalizedDir = MathHelper::Normalize(normalizedDir);
		
		move(normalizedDir * ((getTextureRect().width + other->getTextureRect().width) / 2.0f - dist));
	}
	else
	{
		if(getPosition().x < other->getPosition().x - other->getTextureRect().width / 2)
		{
			float ownX = getPosition().x + m_collider->m_fRadius;
			float otherX = other->getPosition().x - other->getTextureRect().width / 2;
			move(otherX - ownX,0);
		}
		else if(getPosition().x > other->getPosition().x + other->getTextureRect().width / 2)
		{
			float ownX = getPosition().x - m_collider->m_fRadius;
			float otherX = other->getPosition().x + other->getTextureRect().width / 2;
			move(otherX - ownX,0);
		}

		if(getPosition().y < other->getPosition().y - other->getTextureRect().height / 2)
		{
			float ownY = getPosition().y + m_collider->m_fRadius;
			float otherY = other->getPosition().y - other->getTextureRect().height / 2;
			move(0, otherY - ownY);
		}
		else if(getPosition().y > other->getPosition().y + other->getTextureRect().height / 2)
		{
			float ownY = getPosition().y - m_collider->m_fRadius;
			float otherY = other->getPosition().y + other->getTextureRect().height / 2;
			move(0, otherY - ownY);
		}
	}

	if(other->GetType() == "Bullet")
	{
		if(((Bullet*)(other))->m_owner != this)
		{
			m_fHealth -= 10;
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