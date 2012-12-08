#pragma once
#include "Collider.h"
class GameObject :
	public sf::Sprite
{
public:
	GameObject(void);
	GameObject(std::string, bool circularCollision = true);
	virtual ~GameObject(void);

	virtual std::string GetType(void);

	bool m_bCanDie;
	bool m_bIsDead;
	bool m_bIsCollidable;
	float m_fHealth;
	bool isColliding(GameObject*);

	virtual void Update(float);
	virtual void Die(void);
	virtual void Hit(GameObject* other);
	virtual std::string GetName(void);
	void LoadFromPath(std::string);
	Collider* m_collider;
protected:
	float m_fMaximumSpeed;
	float m_fRotation;
	std::string m_name;
	sf::Texture *texture;
};
