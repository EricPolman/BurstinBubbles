#pragma once
#include "gameobject.h"
#include "gameobject.h"

class Medipack :
	public GameObject
{
public:
	Medipack(void);
	virtual ~Medipack(void);

	virtual void Hit(GameObject* other);
	virtual std::string GetType(void);
};

