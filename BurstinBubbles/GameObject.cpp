#include "StdAfx.h"
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(void)
{
}


GameObject::GameObject(std::string imagePath)
{
	LoadFromPath(imagePath);
	m_fMaximumSpeed = 200;
}


GameObject::~GameObject(void)
{
}


void GameObject::Update(float fDeltaTime)
{
	
}


void GameObject::LoadFromPath(std::string imagePath)
{
	setTexture(TextureManager::getInstance()->m_Textures[imagePath]);
	setOrigin(getTexture()->getSize().x / 2, getTexture()->getSize().y / 2);
}


void GameObject::Die(void)
{

}


bool GameObject::isColliding(GameObject *other)
{
	if(Distance(getPosition(), other->getPosition()) < (getTextureRect().width + other->getTextureRect().width) / 2)
	{
		return true;
	}

	return false;
}

float GameObject::Distance(sf::Vector2f a, sf::Vector2f b)
{
	float result = std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	return result;
}