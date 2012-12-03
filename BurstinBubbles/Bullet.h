#pragma once
#include "gameobject.h"
class Bullet :
	public GameObject
{
public:
	Bullet(void);
	~Bullet(void);
	virtual std::string GetType(void);

	GameObject* m_owner;
	sf::Vector2f m_direction;
	float m_fSpeed;
	float m_fBulletLifetime;
	virtual void Update(float);
	virtual void Hit(GameObject* other);
};