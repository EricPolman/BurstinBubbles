#include "StdAfx.h"
#include "TextureManager.h"


TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
	instanceFlag = false;
	for(std::map<std::string, sf::Texture*>::iterator i = m_Textures.begin(); i != m_Textures.end(); ++i)
	{
		m_Textures.erase(i);
	}
}

bool TextureManager::instanceFlag = false;
TextureManager* TextureManager::single = NULL;
TextureManager* TextureManager::getInstance()
{
    if(! instanceFlag)
    {
        single = new TextureManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}