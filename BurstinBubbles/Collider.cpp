#include "StdAfx.h"
#include "Collider.h"


Collider::Collider(void)
{
}


Collider::Collider(const sf::Vector2f* position,float radius)
{
	IsCircular = true;
	m_fRadius = radius;
	m_position = position;
}


Collider::Collider(const sf::Vector2f* position, const sf::IntRect& boundingBox)
{
	IsCircular = false;
	m_boundingBox = &boundingBox;
	m_position = position;
}


Collider::~Collider(void)
{
}


bool Collider::Intersects(Collider* other)
{
	if(IsCircular)
	{
		if(other->IsCircular)
		{
			if(Distance(*m_position, *(other->m_position)) < m_fRadius + other->m_fRadius)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			sf::Vector2f direction = *(other->m_position) - *m_position;
			direction = NormalizeVector(direction);
			direction *= m_fRadius;
			direction += *m_position;
			
			int left = other->m_boundingBox->left - (other->m_boundingBox->width / 2) + other->m_position->x;
			int top = other->m_boundingBox->top - (other->m_boundingBox->height / 2) + other->m_position->y;
			sf::IntRect rect(left, top, other->m_boundingBox->width, other->m_boundingBox->height); 

			if(direction.x > rect.left && direction.x < rect.left + rect.width
				&& direction.y > rect.top && direction.y < rect.top + rect.width)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if(other->IsCircular)
		{
			sf::Vector2f direction = *m_position - *(other->m_position);
			direction = NormalizeVector(direction);
			direction *= other->m_fRadius;
			direction += *(other->m_position);

			int left = m_boundingBox->left - (m_boundingBox->width / 2) + m_position->x;
			int top = m_boundingBox->top - (m_boundingBox->height / 2) + m_position->y;
			sf::IntRect rect(left, top, m_boundingBox->width, m_boundingBox->height); 

			if(direction.x > rect.left && direction.x < rect.left + rect.width
				&& direction.y > rect.top && direction.y < rect.top + rect.width)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			/*
			 *	TODO: RECT/RECT collision.
			 */
			return false;
		}
	}

	return false;
}


sf::Vector2f Collider::NormalizeVector(sf::Vector2f vec)
{
	float mag = Distance(sf::Vector2f(0,0), vec);
	return sf::Vector2f(vec.x / mag, vec.y / mag);
}


float Collider::Distance(sf::Vector2f a, sf::Vector2f b)
{
	float result = std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	return result;
}