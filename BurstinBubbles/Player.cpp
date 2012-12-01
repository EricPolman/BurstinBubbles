#include "StdAfx.h"
#include "Player.h"

float shootTimer = 0;
float SHOOT_TIME = 0.2f;

Player::Player(void)
{
}


Player::~Player(void)
{
}


Player::Player(const Player& player) : GameObject("player")
{
	m_bullets = player.m_bullets;
	setTextureRect(sf::IntRect(0,0,100,100));
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	m_fMaximumSpeed = 150.0f;
}


Player::Player(std::string imagePath) : GameObject(imagePath)
{
	setTextureRect(sf::IntRect(0,0,100,100));
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	m_fMaximumSpeed = 150.0f;
}


void Player::Update(float fDeltaTime)
{
	GameObject::Update(fDeltaTime);
	sf::Vector2f direction(std::cos(PI * (getRotation() - 90) / 180.0f), std::sin(PI * (getRotation() - 90) / 180.0f));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotate(-135 * fDeltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotate(135 * fDeltaTime);
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
	shootTimer += fDeltaTime;
}


void Player::Die(void)
{
}


void Player::Shoot(void)
{
	Bullet* bullet = new Bullet();
	bullet->m_direction = sf::Vector2f(std::cos(PI * (getRotation() - 90) / 180.0f), std::sin(PI * (getRotation() - 90) / 180.0f));
	bullet->setPosition(getPosition() + bullet->m_direction * (float)(getTextureRect().width / 2));

	m_bullets.push_back(bullet);
}


void Player::Hit(GameObject* other)
{
	sf::Vector2f normalizedDir = getPosition() - other->getPosition();
	float dist = Distance(getPosition(), other->getPosition());
	normalizedDir.x /= dist;
	normalizedDir.y /= dist;

	move(normalizedDir * ((getTextureRect().width + other->getTextureRect().width) / 2 - dist));
}