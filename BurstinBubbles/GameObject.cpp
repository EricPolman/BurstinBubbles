#include "StdAfx.h"
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(void)
{
}


GameObject::GameObject(std::string imagePath)
{
	GameObject::LoadFromPath(imagePath);
	m_fMaximumSpeed = 250;
	m_bCanDie = false;
	m_bIsDead = false;
	m_bIsCollidable = true;
	m_fHealth = 100;
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


void GameObject::Hit(GameObject* other)
{

}


std::string GameObject::GetType(void)
{
	return "GameObject";
}


sf::Vector2f GameObject::NormalizeVector(sf::Vector2f vec)
{
	float mag = Distance(sf::Vector2f(0,0), vec);
	return sf::Vector2f(vec.x / mag, vec.y / mag);
}


sf::Vector2f GameObject::LerpVector(sf::Vector2f a, sf::Vector2f b, float amount)
{
	sf::Vector2f diff = b - a;
	return a + diff * amount;
}


