#include "StdAfx.h"
#include "GUIMuteButton.h"

GUIMuteButton::GUIMuteButton(void) : GUIButton()
{
	mute = false;
	setTextureRect(sf::IntRect(0,0,60,60));
	setOrigin(30,30);
}


GUIMuteButton::~GUIMuteButton(void)
{
}


void GUIMuteButton::Update(float fDeltaTime, sf::Vector2f mousePosition)
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

	if(mute)
	{
		setTexture(*TextureManager::getInstance()->m_Textures["music_off"]);
	}
	else
	{
		setTexture(*TextureManager::getInstance()->m_Textures["music_on"]);
	}
}