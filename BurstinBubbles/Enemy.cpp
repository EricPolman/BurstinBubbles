#include "StdAfx.h"
#include "Enemy.h"
#include "Bullet.h"

Player* Enemy::g_player;
float fSHOOT_TIME = 0.8f;

Enemy::Enemy(void) : GameObject("enemy")
{
	Enemy::fCurrentEnemies++;
	delete m_collider;
	m_collider = new Collider(&(getPosition()), getTextureRect().width / 2.0f);
	fSHOOT_TIME = 0.6f + MathHelper::Random(0.6f);
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
	//Enemy::fCurrentEnemies = 0;
	fKilledEnemies++;
}


void Enemy::Update(float fDeltaTime)
{
	sf::Uint8 healthVal = (2.55f * m_fHealth);
	setColor(sf::Color(getColor().r, healthVal, healthVal, 255));

	sf::Vector2f dir(sf::Vector2f(g_player->getPosition().x,g_player->getPosition().y) - getPosition());
	dir = MathHelper::Normalize(dir);
	float newRot = asinf(dir.x) * 180 / PI;
	if(dir.y >0)
	{	
		newRot = 180 - newRot;
	}
	setRotation(newRot);

	m_fShootTimer += fDeltaTime;
	
	if(MathHelper::Distance(g_player->getPosition(), getPosition()) > 350)
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
		if(other->GetType() != "Bullet")
		{
			sf::Vector2f normalizedDir = getPosition() - other->getPosition();
			float dist = MathHelper::Distance(getPosition(), other->getPosition());
			normalizedDir = MathHelper::Normalize(normalizedDir);
		
			move(normalizedDir * ((getTextureRect().width + other->getTextureRect().width) / 2.0f - dist));
		}
	}
	else
	{
		if(getPosition().x + m_collider->m_fRadius < other->getPosition().x - other->getTextureRect().width / 2)
		{
			float ownX = getPosition().x + m_collider->m_fRadius;
			float otherX = other->getPosition().x - other->getTextureRect().width / 2;
			move(otherX - ownX,0);
		}
		else if(getPosition().x - m_collider->m_fRadius > other->getPosition().x + other->getTextureRect().width / 2)
		{
			float ownX = getPosition().x - m_collider->m_fRadius;
			float otherX = other->getPosition().x + other->getTextureRect().width / 2;
			move(otherX - ownX,0);
		}

		if(getPosition().y - m_collider->m_fRadius < other->getPosition().y - other->getTextureRect().height / 2)
		{
			float ownY = getPosition().y + m_collider->m_fRadius;
			float otherY = other->getPosition().y - other->getTextureRect().height / 2;
			move(0, otherY - ownY);
		}
		else if(getPosition().y + m_collider->m_fRadius > other->getPosition().y + other->getTextureRect().height / 2)
		{
			float ownY = getPosition().y - m_collider->m_fRadius;
			float otherY = other->getPosition().y + other->getTextureRect().height / 2;
			move(0, otherY - ownY);
		}

		if(getPosition().y + m_collider->m_fRadius > other->getPosition().y - other->getTextureRect().height / 2 &&
		   getPosition().y - m_collider->m_fRadius < other->getPosition().y + other->getTextureRect().height / 2 &&
		   getPosition().x - m_collider->m_fRadius < other->getPosition().x + other->getTextureRect().width / 2 &&
		   getPosition().x + m_collider->m_fRadius > other->getPosition().x - other->getTextureRect().width / 2)
		{
			sf::Vector2f dir = MathHelper::Normalize(getPosition() - other->getPosition());
			move(dir * 10.0f);
		}
	}

	if(other->GetType() == "Bullet")
	{
		if(((Bullet*)(other))->m_owner != this)
		{
			m_fHealth -= 15;
			SoundManager::getInstance()->Play("impact_body", 70.f, true);
		}
	}
}


void Enemy::Shoot(void)
{
	Bullet* bullet = new Bullet();
	bullet->m_direction = sf::Vector2f(std::cos(PI * (getRotation() + (-9 + 18*MathHelper::Random()) - 90) / 180.0f), std::sin(PI * (getRotation() + (-9 + 18*MathHelper::Random()) - 90) / 180.0f));
	bullet->setPosition(getPosition() + bullet->m_direction * (float)(getTextureRect().width / 2));
	bullet->m_owner = this;
	SoundManager::getInstance()->Play("shoot_enemy", 50.f, true);
	m_bullets.push_back(bullet);
}


std::string Enemy::GetType(void)
{
	return "Enemy";
}