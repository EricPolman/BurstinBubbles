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
}


GameObject::~GameObject(void)
{
}


void GameObject::Update(float fDeltaTime)
{
	
}


void GameObject::LoadFromPath(std::string imagePath)
{
	if(!texture->loadFromFile(imagePath))
	{
		std::cout << "Couldn't load " << imagePath;
	}
	setTexture(*texture);
	setPosition(100, 25);
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