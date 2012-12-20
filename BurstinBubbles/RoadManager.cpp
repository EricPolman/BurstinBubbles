#include "StdAfx.h"
#include "RoadManager.h"


RoadManager::RoadManager()
{
	m_iGridSizeX = 7;
	m_iGridSizeY = 7;
}


RoadManager::~RoadManager(void)
{
}


RoadManager::RoadManager(const RoadManager& other)
{
}


void RoadManager::AlignToPlayer(GameObject* player, bool alignX, bool alignY)
{
	sf::Vector2f center(SettingHelper::g_iWindowWidth / 2, SettingHelper::g_iWindowHeight / 2);
	sf::Vector2f translation = center - player->getPosition();

	if(!alignX)
		translation.x = 0;
	if(!alignY)
		translation.y = 0;

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
			if(x % 2 == 0 && y % 2 == 0)
			{
				roadPieces[x][y] = new GameObject("road_intersection");
			}
			else if(x % 2 == 1 && y % 2 == 0)
			{
				roadPieces[x][y] = new GameObject("road_horizontal");
			}
			else if(x % 2 == 0 && y % 2 == 1)
			{
				roadPieces[x][y] = new GameObject("road_vertical");
			}
			else
			{
				roadPieces[x][y] = new GameObject("field_grass");
			}
			
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