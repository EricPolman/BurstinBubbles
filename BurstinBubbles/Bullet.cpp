#include "StdAfx.h"
#include "Bullet.h"

Bullet::Bullet(void)
{
	m_fBulletLifetime = 0;
}


Bullet::~Bullet(void)
{
}


void Bullet::Update(float fDeltaTime)
{
	move(m_direction * m_fSpeed * fDeltaTime);
	m_fBulletLifetime += fDeltaTime;
}