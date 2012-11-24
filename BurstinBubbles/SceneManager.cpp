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
	m_currentScene.Update(fDeltaTime);
}


void SceneManager::LoadScene(std::string sFile)
{
	m_currentScene.LoadFromFile(g_sRootPath + "\\" + sFile);
}


void SceneManager::UnloadScene(void)
{
}


void SceneManager::Draw(sf::RenderWindow *window)
{
	m_currentScene.Draw(window);
}