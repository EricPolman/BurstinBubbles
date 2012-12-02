#include "StdAfx.h"
#include "Player.h"

float shootTimer = 0;
float SHOOT_TIME = 0.1f;

Player::Player(void)
{
}


Player::~Player(void)
{
}


Player::Player(const Player& player) : GameObject("player")
{
	m_bullets = player.m_bullets;
	Init();
}


Player::Player(std::string imagePath) : GameObject(imagePath)
{
	Init();
}

void Player::Init()
{
	setTextureRect(sf::IntRect(0,0,100,100));
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	m_fMaximumSpeed = 300.0f;
	m_mousePosition.x = 10;
	m_mousePosition.y = 10;
}


void Player::UpdateMouse(sf::RenderWindow& Window)
{
	m_mousePosition = sf::Mouse::getPosition(Window);
}


void Player::Update(float fDeltaTime)
{
	GameObject::Update(fDeltaTime);

	sf::Vector2f dir(sf::Vector2f(m_mousePosition.x,m_mousePosition.y) - getPosition());
	float mag = Distance(sf::Vector2f(m_mousePosition.x,m_mousePosition.y), getPosition());
	dir.x /= mag;
	dir.y /= mag;
	std::cout << asinf(dir.x) * 180 / PI << std::endl;
	float newRot = asinf(dir.x) * 180 / PI;
	if(dir.y >0)
	{	
		newRot = 180 - newRot;
	}
	
	setRotation(newRot);
	sf::Vector2f direction(std::cos(PI * (getRotation() - 90) / 180.0f), std::sin(PI * (getRotation() - 90) / 180.0f));
	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(fDeltaTime * m_fMaximumSpeed, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(-fDeltaTime * m_fMaximumSpeed, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(0, -fDeltaTime * m_fMaximumSpeed); 
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move(0, -fDeltaTime * m_fMaximumSpeed);
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