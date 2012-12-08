#include "StdAfx.h"
#include "RoadManager.h"


RoadManager::RoadManager()
{
	m_iGridSizeX = 11;
	m_iGridSizeY = 11;
}


RoadManager::~RoadManager(void)
{
}


RoadManager::RoadManager(const RoadManager& other)
{
}


void RoadManager::AlignToPlayer(GameObject* player)
{
	sf::Vector2f center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	sf::Vector2f translation = center - player->getPosition();

	for(int x = 0; x < m_iGridSizeX; x++)
	{
		for(int y = 0; y < m_iGridSizeY; y++)
		{
			roadPieces[x][y]->move(translation);
		}
	}
}


void RoadManager::Generate(void)
{
	float random = MathHelper::Random();
	

	for(int x = 0; x < m_iGridSizeX; x++)
	{
		for(int y = 0; y < m_iGridSizeY; y++)
		{
			roadPieces[x][y] = new GameObject("road_intersection");
			
			roadPieces[x][y]->move((m_iGridSizeX / 2.0f * -512) + 512 * x, (m_iGridSizeY / 2.0f * -768) + 768 * y);
		}
	}
}


void RoadManager::Draw(sf::RenderWindow* window)
{
	for(int x = 0; x < m_iGridSizeX; x++)
	{
		for(int y = 0; y < m_iGridSizeY; y++)
		{
			window->draw(*(roadPieces[x][y]));
		}
	}
}