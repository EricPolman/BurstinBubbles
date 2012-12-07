#include "MathHelper.h"

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0,1);

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


float MathHelper::Random(float range)
{
	float rnd = distribution(generator);
	return rnd;
}