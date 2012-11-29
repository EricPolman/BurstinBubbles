#pragma once
#include "gameobject.h"
#include <vector>
#include "bullet.h"

class Player :
	public GameObject
{
public:
	Player(void);
	Player(std::string);
	~Player(void);

	virtual void Update(float);
	virtual void Shoot(void);
	void LoadFromPath(std::string);
	virtual void Die(void);

	std::vector<Bullet> m_bullets;
};