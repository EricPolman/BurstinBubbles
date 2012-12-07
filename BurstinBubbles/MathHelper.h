#pragma once
#include "SFML\Graphics.hpp"
#include <random>

class MathHelper
{
public:
	static float Magnitude(sf::Vector2f vec);
	static float Distance(sf::Vector2f vecA, sf::Vector2f vecB);
	static sf::Vector2f Normalize(sf::Vector2f vec);
	static float Random(float range = 1);
};