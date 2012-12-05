#include "StdAfx.h"
#include "MathHelper.h"

float MathHelper::Magnitude(sf::Vector2f vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}


float MathHelper::Distance(sf::Vector2f vecA, sf::Vector2f vecB)
{
	return Magnitude(vecB - vecA);
}


sf::Vector2f MathHelper::Normalize(sf::Vector2f vec)
{
	float mag = Magnitude(vec);
	return sf::Vector2f(vec.x / mag, vec.y / mag);
}


