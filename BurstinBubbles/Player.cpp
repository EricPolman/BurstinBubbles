#include "StdAfx.h"
#include "Player.h"

float shootTimer = 0;
float SHOOT_TIME = 0.25f;

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
	m_bullets.clear();

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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if(shootTimer > SHOOT_TIME)
		{
			shootTimer = 0;
			Shoot();
		}
	}

	shootTimer+=fDeltaTime;
}


void Player::Die(void)
{
}


void Player::Shoot(void)
{
	Bullet bullet;
	bullet.m_direction = sf::Vector2f(std::cos(PI * (getRotation() - 90) / 180.0f), std::sin(PI * (getRotation() - 90) / 180.0f));
	bullet.m_fSpeed = 500;
	bullet.setPosition(getPosition() + bullet.m_direction);
	bullet.LoadFromPath("bullet");

	m_bullets.push_back(bullet);
}