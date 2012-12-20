#pragma once
#include "guielement.h"
class GUIButton :
	public GUIElement
{
public:
	GUIButton(void);
	~GUIButton(void);

	virtual void Update(float fDeltaTime, sf::Vector2f mousePosition);
	bool GetClicked(void);
	bool GetHover(void);
	bool GetDown(void);
	void UpdateButtonRect(void);
	bool m_bMouseDown;
	bool m_bMouseHover;
	bool m_bMouseClick;
	bool m_bOldMouseDown;
	bool m_bOldMouseHover;
	bool m_bOldMouseClick;
	bool intersectsRect(sf::Vector2i);
protected:
	sf::IntRect m_buttonRect;
};