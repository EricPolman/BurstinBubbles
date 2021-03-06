#pragma once
#include "GameObjectManager.h"
#include "RoadManager.h"
#include "SFML/Graphics.hpp"
#include "Enemy.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);

	GameObjectManager* m_GameObjectManager;
	RoadManager* m_roadManager;

	void Update(float);
	void LoadFromFile(std::string);
	void Draw(sf::RenderWindow*);
	void RandomlyPlaceObjects(std::string name, int amount, sf::IntRect range);

	sf::Sprite m_lifeBar;
	sf::Sprite m_lifeBarRed;

	bool m_bPlayerIsDead;
	bool m_bScenePlaying;
	sf::Font* m_font;

	sf::Text m_lifebarText;
	sf::Text m_killText;

private:
	bool m_bCameraFollowsPlayerX;
	bool m_bCameraFollowsPlayerY;
};

