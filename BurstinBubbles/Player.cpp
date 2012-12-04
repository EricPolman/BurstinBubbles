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
	setTextureRect(sf::IntRect(0,0,50,50));
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	m_fMaximumSpeed = 200.0f;
	m_mousePosition.x = 10;
	m_mousePosition.y = 10;
	m_bIsDead = false;
}


void Player::UpdateMouse(sf::RenderWindow& Window)
{
	m_mousePosition = sf::Mouse::getPosition(Window);
}


void Player::Update(float fDeltaTime)
{
	GameObject::Update(fDeltaTime);

	sf::Vector2f dir(sf::Vector2f(m_mousePosition.x,m_mousePosition.y) - getPosition());
	dir = NormalizeVector(dir);

	float newRot = asinf(dir.x) * 180 / PI;
	if(dir.y >0)
	{	
		newRot = 180 - newRot;
	}
	
	setRotation(newRot);
	
	sf::Vector2f moveDir(0,0);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveDir.x += 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveDir.x -= 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveDir.y -= 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveDir.y += 1;
	}
	if(moveDir.x != 0 && moveDir.y != 0)
	{
		float magMove = Distance(sf::Vector2f(0,0), moveDir);
		moveDir.x /= magMove;
		moveDir.y /= magMove;
	}

	move(-fDeltaTime * m_fMaximumSpeed * moveDir);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if(shootTimer > SHOOT_TIME)
		{
			shootTimer = 0;
			Shoot();
		}
	}
	shootTimer += fDeltaTime;

	if(m_fHealth < 1)
	{
		Die();
	}
}


void Player::Die(void)
{
	m_bIsDead = true;
}


void Player::Shoot(void)
{
	Bullet* bullet = new Bullet();
	bullet->m_direction = sf::Vector2f(std::cos(PI * (getRotation() - 90) / 180.0f), std::sin(PI * (getRotation() - 90) / 180.0f));
	bullet->setPosition(getPosition() + bullet->m_direction * (float)(getTextureRect().width / 2));
	bullet->m_owner = this;
	m_bullets.push_back(bullet);
}


void Player::Hit(GameObject* other)
{
	sf::Vector2f normalizedDir = getPosition() - other->getPosition();
	float dist = Distance(getPosition(), other->getPosition());
	normalizedDir = NormalizeVector(normalizedDir);

	move(normalizedDir * ((getTextureRect().width + other->getTextureRect().width) / 2 - dist));

	if(other->GetType() == "Bullet" && ((Bullet*)other)->m_owner != this)
	{
		m_fHealth -= 3;
	}
}


std::string Player::GetType(void)
{
	return "Player";
}