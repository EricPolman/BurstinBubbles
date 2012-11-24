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

	void Update(float);
	void LoadFromPath(std::string);
	void Die(void);
private:
	float m_fMaximumSpeed;
	float m_fRotation;
};

