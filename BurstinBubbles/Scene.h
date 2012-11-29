#pragma once
#include "GameObjectManager.h"
#include "SFML/Graphics.hpp"

class Scene
{
public:
	Scene(void);
	~Scene(void);

	GameObjectManager m_GameObjectManager;
	void Update(float);
	void LoadFromFile(std::string);
	void Draw(sf::RenderWindow*);

private:
	bool m_bCameraFollowsPlayer;
};

