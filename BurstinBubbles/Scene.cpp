#include "StdAfx.h"
#include "Scene.h"

Scene::Scene(void)
{
	m_bCameraFollowsPlayer = true;
}


Scene::~Scene(void)
{
}


void Scene::Update(float fDeltaTime)
{
	m_GameObjectManager.Update(fDeltaTime);
	if(m_bCameraFollowsPlayer)
	{
		m_GameObjectManager.CenterPlayer();
	}
}


void Scene::Draw(sf::RenderWindow *window)
{
	m_GameObjectManager.Draw(window);
}


void Scene::LoadFromFile(std::string sFile)
{
	/*
	 *	TODO: Implement loading of .scene-file. Placing assets, players, enemies, etc through GameObjectManager.
	 */
}