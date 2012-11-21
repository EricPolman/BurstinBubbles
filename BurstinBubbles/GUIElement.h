#pragma once
#include "SFML\Graphics.hpp"

class GUIElement :
	public sf::Sprite
{
public:
	GUIElement(void);
	virtual ~GUIElement(void);
};

