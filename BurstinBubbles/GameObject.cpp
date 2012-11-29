#include "StdAfx.h"
#include "GameObject.h"

GameObject::GameObject(void)
{
}


GameObject::GameObject(std::string imagePath)
{
	texture = new sf::Texture();
	LoadFromPath(imagePath);
	setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	m_fMaximumSpeed = 200;
	std::cout << " " << texture->getSize().x << std::endl;
}


GameObject::~GameObject(void)
{
}


void GameObject::Update(float fDeltaTime)
{
	
}


void GameObject::LoadFromPath(std::string imagePath)
{
	std::cout << imagePath;
	if(!texture->loadFromFile(imagePath))
	{
		std::cout << "1";
	}
	setTexture(*texture);
	setPosition(100, 25);
}


void GameObject::Die(void)
{

}