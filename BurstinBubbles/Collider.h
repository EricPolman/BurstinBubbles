#pragma once
#include "stdafx.h"

class Collider
{
public:
	Collider(void);
	Collider(const sf::Vector2f* position, float radius);
	Collider(const sf::Vector2f* position, const sf::IntRect& boundingBox);
	virtual ~Collider(void);

	bool IsCircular;
	bool Intersects(Collider* other);

	const sf::Vector2f* m_position;

	float m_fRadius;
	const sf::IntRect* m_boundingBox;
};

