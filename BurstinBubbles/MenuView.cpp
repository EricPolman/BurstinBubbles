#include "StdAfx.h"
#include "MenuView.h"


MenuView::MenuView(void)
{
}


MenuView::~MenuView(void)
{
}


void MenuView::Update(float fDeltaTime, sf::Vector2f mousePosition)
{
	for(std::vector<GUIElement*>::iterator i = m_guiElements.begin(); i != m_guiElements.end(); i++)
	{
		(*i)->Update(fDeltaTime, mousePosition);
	}
}


void MenuView::Draw(sf::RenderWindow* Window)
{
	for(std::vector<GUIElement*>::iterator i = m_guiElements.begin(); i != m_guiElements.end(); i++)
	{
		Window->draw(*(*i));
	}
}


void MenuView::Add(GUIElement* toAdd)
{
	m_guiElements.push_back(toAdd);
}