#pragma once
#include "GUIMuteButton.h"
#include "TextureManager.h"

class MenuView
{
public:
	MenuView(void);
	~MenuView(void);

	void Update(float fDeltaTime, sf::Vector2f mousePosition);
	void Draw(sf::RenderWindow* Window);
	void Add(GUIButton* toAdd);
	void LoadTexture(std::string path, std::string name);
	std::vector<GUIButton*> m_guiButtons;
};