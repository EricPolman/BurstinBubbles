#pragma once
#include "SFML\Graphics.hpp"

class GameObject :
	public sf::Sprite
{
public:
	GameObject(void);
	GameObject(std::string);
	virtual ~GameObject(void);

	bool m_bCanDie;
	bool m_bIsDead;
	bool m_bIsCollidable;
	float m_fHealth;
	bool isColliding(GameObject*);

	virtual void Update(float);
	virtual void Die(void);
	virtual void Hit(GameObject* other);

	void LoadFromPath(std::string);
	
	float Distance(sf::Vector2f, sf::Vector2f);

protected:
	float m_fMaximumSpeed;
	float m_fRotation;
	sf::Texture *texture;
};

