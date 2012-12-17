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
private:
	bool m_bMouseDown;
	bool m_bMouseHover;
	bool m_bMouseClick;
};