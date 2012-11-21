#include "Scene.h"
#include <string>
#include <list>

#pragma once
class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);

	void LoadScene(std::string);
	void UnloadScene(void);
	void Update(float);

private:
	std::string g_sRootPath;
	std::list<std::string> *m_loadableScenes;
	Scene *m_currentScene;
};

