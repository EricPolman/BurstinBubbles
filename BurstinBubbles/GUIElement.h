#pragma once
#include "GameObject.h"
#include "TextureManager.h"

class GUIElement :
	public GameObject
{
public:
	GUIElement(void);
	virtual ~GUIElement(void);

	virtual void Update(float fDeltaTime, sf::Vector2f mousePosition);
};

