#pragma once
#include "gameobject.h"
#include "Player.h"

class Enemy :
	public GameObject
{
public:
	Enemy(void);
	Enemy(const Enemy&);
	~Enemy(void);
	virtual std::string GetType(void);
	static Player* g_player;
	virtual void Hit(GameObject*);
	virtual void Shoot(void);
	virtual void Update(float);
	virtual void Die(void);
	std::vector<Bullet*> m_bullets;

	static int fMAX_ACTIVE_ENEMIES;
	static int fCurrentEnemies;
	static int fKilledEnemies;
private:
	float m_fShootTimer;
};

