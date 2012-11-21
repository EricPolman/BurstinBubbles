#pragma once
#include "SFML\Graphics.hpp"

class GameObject :
	public sf::Sprite
{
public:
	GameObject(void);
	virtual ~GameObject(void);
};

