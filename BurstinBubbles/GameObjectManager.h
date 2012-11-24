#pragma once
#include <vector>
#include "GameObject.h"
#include "SFML/Graphics.hpp"

class GameObjectManager
{
public:
	GameObjectManager(void);
	~GameObjectManager(void);
	void Update(float);
	void Draw(sf::RenderWindow*);
	void Remove(GameObject*);
	void Add(GameObject*);
private:
	std::vector<GameObject> m_gameObjects;
};

