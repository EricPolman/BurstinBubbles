#include "StdAfx.h"
#include "GameObject.h"


sf::Texture *texture;

GameObject::GameObject(void)
{
	texture = new sf::Texture();
	LoadFromPath("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Sprites/enemy.png");
	setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	m_fMaximumSpeed = 200;
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
	//delete texture;
}


void GameObject::Update(float fDeltaTime)
{
	sf::Vector2f direction(std::cos(PI * (getRotation() - 90) / 180.0f), std::sin(PI * (getRotation() - 90) / 180.0f));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotate(-180 * fDeltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotate(180 * fDeltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(-direction * fDeltaTime * m_fMaximumSpeed * 0.5f); 
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move(direction * fDeltaTime * m_fMaximumSpeed);
	}
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