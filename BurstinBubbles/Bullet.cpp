#include "StdAfx.h"
#include "Bullet.h"

Bullet::Bullet(void) : GameObject("bullet")
{
	m_fBulletLifetime = 0;
	m_bCanDie = true;
	m_bIsCollidable = true;
	m_fMaximumSpeed = 600.0f;
}


Bullet::Bullet(const Bullet&) : GameObject("bullet")
{
}


Bullet::~Bullet(void)
{
}


void Bullet::Update(float fDeltaTime)
{
	move(m_direction * m_fMaximumSpeed * fDeltaTime);
	m_fBulletLifetime += fDeltaTime;

	if(m_fBulletLifetime > 3)
		m_bIsDead = true;
}

void Bullet::Hit(GameObject* other)
{
	if(other != m_owner)
	{
		m_bIsDead = true;
	}
}


std::string Bullet::GetType(void)
{
	return "Bullet";
}