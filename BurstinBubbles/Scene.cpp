#include "StdAfx.h"
#include "Scene.h"

Scene::Scene(void)
{
	std::cout << "Scene created.";
}


Scene::~Scene(void)
{
}


void Scene::Update(float fDeltaTime)
{

}


void Scene::LoadFromFile(std::string sFile)
{
	std::cout << "Loading scene from file: " << sFile.c_str() << std::endl;
	/*
	 *	TODO: Implement loading of .scene-file. Placing assets, players, enemies, etc through GameObjectManager.
	 */
}