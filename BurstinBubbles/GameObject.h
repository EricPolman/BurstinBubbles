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

	virtual void Update(float);
	void LoadFromPath(std::string);
	virtual void Die(void);
protected:
	float m_fMaximumSpeed;
	float m_fRotation;
	sf::Texture *texture;
};

