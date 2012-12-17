#pragma once
#include"GUIButton.h"

class MenuView
{
public:
	MenuView(void);
	~MenuView(void);

	void Update(float fDeltaTime, sf::Vector2f mousePosition);
	void Draw(sf::RenderWindow* Window);
	void Add(GUIElement* toAdd);
private:
	std::vector<GUIElement*> m_guiElements;
};