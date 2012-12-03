#pragma once
#include "gameobject.h"
#include "Player.h"

class Enemy :
	public GameObject
{
public:
	Enemy(void);
	virtual ~Enemy(void);
	virtual std::string GetType(void);
	static Player* g_player;
	virtual void Hit(GameObject*);
	virtual void Update(float);
};

