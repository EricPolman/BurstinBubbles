#pragma once
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

class GameObjectManager
{
public:
	GameObjectManager(void);
	GameObjectManager(const GameObjectManager&);
	~GameObjectManager(void);

	void Update(float);
	void Draw(sf::RenderWindow*);
	void Remove(GameObject*);
	void Add(GameObject*);
	Player* m_player;
	void CenterPlayer(bool alignX, bool alignY);
private:
	std::vector<GameObject*> m_gameObjects;
	
};

