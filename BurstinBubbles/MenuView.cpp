#include "StdAfx.h"
#include "MenuView.h"


MenuView::MenuView(void)
{
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/button/hover.png", "button_hover");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/button/normal.png", "button_normal");
	LoadTexture(SettingHelper::g_sRootPath + "/Data/Sprites/button/down.png", "button_down");
}


MenuView::~MenuView(void)
{
}


void MenuView::Update(float fDeltaTime, sf::Vector2f mousePosition)
{
	for(std::vector<GUIButton*>::iterator i = m_guiButtons.begin(); i != m_guiButtons.end(); i++)
	{
		(*i)->Update(fDeltaTime, mousePosition);
	}
}


void MenuView::Draw(sf::RenderWindow* Window)
{
	for(std::vector<GUIButton*>::iterator i = m_guiButtons.begin(); i != m_guiButtons.end(); i++)
	{
		Window->draw(*(*i));
	}
}


void MenuView::Add(GUIButton* toAdd)
{
	m_guiButtons.push_back(toAdd);
}


void MenuView::LoadTexture(std::string path, std::string name)
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile(path);
	TextureManager::getInstance()->m_Textures[name] = tex;
}