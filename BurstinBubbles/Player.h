#pragma once
#include "gameobject.h"
class Player :
	public GameObject
{
public:
	Player(void);
	Player(std::string);
	~Player(void);

	virtual void Update(float);
	void LoadFromPath(std::string);
	virtual void Die(void);
};