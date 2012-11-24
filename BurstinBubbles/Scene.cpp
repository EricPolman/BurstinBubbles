#include "StdAfx.h"
#include "Scene.h"

Scene::Scene(void)
{
}


Scene::~Scene(void)
{
}


void Scene::Update(float fDeltaTime)
{
	m_GameObjectManager.Update(fDeltaTime);
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