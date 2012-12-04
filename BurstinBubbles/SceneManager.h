#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);

	void LoadScene(std::string);
	void UnloadScene(void);
	void Update(float);
	void Draw(sf::RenderWindow*);
	float m_fSceneRestartTimer;
	void LoadTexture(std::string, std::string);
	sf::Sprite m_loadingScreen;
private:
	std::string g_sRootPath;
	std::vector<std::string> *m_loadableScenes;
	Scene *m_currentScene;
};

