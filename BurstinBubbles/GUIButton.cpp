#include "StdAfx.h"
#include "GUIButton.h"


GUIButton::GUIButton(void) : GUIElement()
{
	m_bMouseDown = false;
	m_bMouseClick = false;
	m_bMouseHover = false;
	m_bOldMouseDown = false;
	m_bOldMouseClick = false;
	m_bOldMouseHover = false;
}


GUIButton::~GUIButton(void)
{
}


void GUIButton::Update(float fDeltaTime, sf::Vector2f mousePosition)
{
	m_bOldMouseClick = m_bMouseClick;
	m_bOldMouseDown = m_bMouseDown;
	m_bOldMouseHover = m_bMouseHover;

	UpdateButtonRect();
	
	if(mousePosition.x > m_buttonRect.left && mousePosition.x < m_buttonRect.left + m_buttonRect.width &&
	   mousePosition.y > m_buttonRect.top && mousePosition.y < m_buttonRect.top + m_buttonRect.height)
	{
		m_bMouseHover = true;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if(!m_bMouseDown)
			{
				m_bMouseClick = true;
			}
			m_bMouseDown = true;
		}
		else
		{
			m_bMouseClick = false;
			m_bMouseDown = false;
		}
	}
	else
	{
		m_bMouseHover = false;
		m_bMouseClick = false;
		m_bMouseDown = false;
	}

	if(m_bMouseDown)
	{
		setTexture(*TextureManager::getInstance()->m_Textures["button_down"]);
	}
	else
	{
		if(m_bMouseHover)
		{
			setTexture(*TextureManager::getInstance()->m_Textures["button_hover"]);
		}
		else
		{
			setTexture(*TextureManager::getInstance()->m_Textures["button_normal"]);
		}
	}
}


void GUIButton::UpdateButtonRect(void)
{
	sf::Vector2f position = getPosition();
	m_buttonRect.left = position.x - getTextureRect().width/2;
	m_buttonRect.top = position.y - getTextureRect().height/2;
	m_buttonRect.width = getTextureRect().width;
	m_buttonRect.height = getTextureRect().height;
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


bool GUIButton::intersectsRect(sf::Vector2i mousePosition)
{
	if(mousePosition.x > m_buttonRect.left && mousePosition.x < m_buttonRect.left + m_buttonRect.width &&
	   mousePosition.y > m_buttonRect.top && mousePosition.y < m_buttonRect.top + m_buttonRect.height)
	{
		return true;
	}

	return false;
}