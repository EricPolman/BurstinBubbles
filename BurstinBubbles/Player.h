#pragma once
#include "gameobject.h"
#include <vector>
#include "bullet.h"

class Player :
	public GameObject
{
public:
	Player(void);
	Player(const Player&);
	Player(std::string);
	~Player(void);

	virtual void Update(float);
	virtual void Shoot(void);
	virtual void Hit(GameObject* other);
	void LoadFromPath(std::string);
	virtual void Die(void);

	std::vector<Bullet*> m_bullets;
};