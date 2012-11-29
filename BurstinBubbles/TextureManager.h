#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <map>


class TextureManager
{
public:
	~TextureManager(void);
	static TextureManager* getInstance(void);

	std::map<std::string, sf::Texture> m_Textures;

private:
	static bool instanceFlag;
	static TextureManager *single;
	TextureManager(void);
};

