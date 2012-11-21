#include "StdAfx.h"
#include "SceneManager.h"
#include "Scene.h"
#include <direct.h>

SceneManager::SceneManager(void)
{
	char CurrentPath[_MAX_PATH];
    _getcwd(CurrentPath, _MAX_PATH);
	g_sRootPath = CurrentPath;
	LoadScene("Data\\Scenes\\default.scene");
}


SceneManager::~SceneManager(void)
{
}


void SceneManager::Update(float fDeltaTime)
{
	m_currentScene->Update(fDeltaTime);
	std::cout << std::endl << "Frame updated. " << fDeltaTime;
}


void SceneManager::LoadScene(std::string sFile)
{
	Scene scene;
	scene.LoadFromFile(g_sRootPath + "\\" + sFile);
	m_currentScene = &scene;
}


void SceneManager::UnloadScene(void)
{
}