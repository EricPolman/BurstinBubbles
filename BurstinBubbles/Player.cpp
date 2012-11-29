#include "StdAfx.h"
#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}


Player::Player(std::string imagePath)
{
	texture = new sf::Texture();
	GameObject::LoadFromPath(imagePath);
	setTextureRect(sf::IntRect(0,0,100,100));
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	m_fMaximumSpeed = 200.0;
}


void Player::Update(float fDeltaTime)
{
	GameObject::Update(fDeltaTime);
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


void Player::Die(void)
{
}