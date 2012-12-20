#pragma once
#include "guibutton.h"
class GUIMuteButton :
	public GUIButton
{
public:
	GUIMuteButton(void);
	~GUIMuteButton(void);

	void Update(float fDeltaTime, sf::Vector2f mousePosition);
	bool mute;
};

