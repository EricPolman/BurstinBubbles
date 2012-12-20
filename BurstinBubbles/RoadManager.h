#pragma once
#include "GameObject.h"

class RoadManager
{
public:
	RoadManager(void);
	RoadManager(const RoadManager&);
	~RoadManager(void);
	
	GameObject* roadPieces[7][7];
	
	int m_iGridSizeX;
	int m_iGridSizeY;

	void Generate(void);
	void Draw(sf::RenderWindow* window);
	void AlignToPlayer(GameObject* player, bool alignX, bool alignY);
};