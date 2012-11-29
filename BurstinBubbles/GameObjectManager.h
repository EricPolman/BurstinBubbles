#pragma once
#include <vector>
#include "GameObject.h"
#include "Player.h"
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
	void AddCollidable(GameObject*);
	void AddPlayer(Player*);

	void CenterPlayer(void);
private:
	std::vector<GameObject> m_gameObjects;
	std::vector<GameObject> m_collidableGameObjects;
	std::vector<Player> m_Players;
};

