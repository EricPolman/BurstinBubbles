#pragma once
#include "gameobject.h"
class Bullet :
	public GameObject
{
public:
	Bullet(void);
	~Bullet(void);
	sf::Vector2f m_direction;
	float m_fSpeed;
	float m_fBulletLifetime;
	virtual void Update(float);
	virtual void Hit(GameObject* other);
};