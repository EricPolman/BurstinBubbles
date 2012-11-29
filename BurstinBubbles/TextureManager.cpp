#include "StdAfx.h"
#include "TextureManager.h"


TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
	instanceFlag = false;
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