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

	void CenterPlayer(void);
private:
	std::vector<GameObject*> m_gameObjects;
	Player* m_player;
};

