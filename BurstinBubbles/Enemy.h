#pragma once
#include "gameobject.h"
#include "Player.h"

class Enemy :
	public GameObject
{
public:
	Enemy(void);
	Enemy(const Enemy&);
	virtual ~Enemy(void);
	virtual std::string GetType(void);
	static Player* g_player;
	virtual void Hit(GameObject*);
	virtual void Shoot(void);
	virtual void Update(float);
	std::vector<Bullet*> m_bullets;
private:
	float m_fShootTimer;
};

