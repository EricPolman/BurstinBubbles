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
	void LoadSound(std::string, std::string, bool loop = false);
	
	sf::Sprite m_loadingScreen;
	sf::Text m_loadingText;
	sf::Text m_restartText;
private:
	std::vector<std::string> *m_loadableScenes;
	Scene *m_currentScene;
};

