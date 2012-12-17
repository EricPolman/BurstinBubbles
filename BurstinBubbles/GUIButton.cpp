#include "StdAfx.h"
#include "GUIButton.h"


GUIButton::GUIButton(void)
{
	m_bMouseDown = false;
	m_bMouseClick = false;
	m_bMouseHover = false;
}


GUIButton::~GUIButton(void)
{
}


void GUIButton::Update(float fDeltaTime, sf::Vector2f mousePosition)
{

}


bool GUIButton::GetDown(void)
{
	return m_bMouseDown;
}


bool GUIButton::GetClicked(void)
{
	return m_bMouseClick;
}


bool GUIButton::GetHover(void)
{
	return m_bMouseHover;
}