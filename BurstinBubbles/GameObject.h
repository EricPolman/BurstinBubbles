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
	float m_fHealth;
	bool isColliding(GameObject*);

	virtual void Update(float);
	void LoadFromPath(std::string);
	virtual void Die(void);
	float Distance(sf::Vector2f, sf::Vector2f);
protected:
	float m_fMaximumSpeed;
	float m_fRotation;
	sf::Texture *texture;
};

