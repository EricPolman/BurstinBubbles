#include "StdAfx.h"
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(void)
{
}


GameObject::GameObject(std::string imagePath, bool circularCollision)
{
	GameObject::LoadFromPath(imagePath);
	m_fMaximumSpeed = 250;
	m_bCanDie = false;
	m_bIsDead = false;
	m_bIsCollidable = true;
	m_fHealth = 100;
	if(circularCollision)
	{
		m_collider = new Collider(&(getPosition()), getTextureRect().width / 2.0f);
	}
	else
	{
		m_collider = new Collider(&(getPosition()), getTextureRect());
	}
}


GameObject::~GameObject(void)
{
	delete m_collider;
}


void GameObject::Update(float fDeltaTime)
{
	
}


void GameObject::LoadFromPath(std::string imagePath)
{
	setTexture(*TextureManager::getInstance()->m_Textures[imagePath]);
	setOrigin(getTexture()->getSize().x / 2, getTexture()->getSize().y / 2);
}


void GameObject::Die(void)
{

}


bool GameObject::isColliding(GameObject *other)
{
	if(MathHelper::Distance(getPosition(), other->getPosition()) < (getTextureRect().width + other->getTextureRect().width) / 2)
	{
		return true;
	}

	return false;
}

void GameObject::Hit(GameObject* other)
{

}


std::string GameObject::GetType(void)
{
	return "GameObject";
}