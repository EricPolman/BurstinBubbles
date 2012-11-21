#include "GameObjectManager.h"

#pragma once
class Scene
{
public:
	Scene(void);
	~Scene(void);

	GameObjectManager m_GameObjectManager;
	void Update(float);
	void LoadFromFile(std::string);
};

