#include "StdAfx.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Medipack.h"

int Enemy::fCurrentEnemies;
int Enemy::fMAX_ACTIVE_ENEMIES;
int Enemy::fTOTAL_ENEMIES_PER_SCENE;
int Enemy::fSPAWNED_ENEMIES_PER_SCENE;

Scene::Scene(void)
{
	m_bScenePlaying = false;

	Enemy::fCurrentEnemies = 0;
	Enemy::fMAX_ACTIVE_ENEMIES = 12;
	Enemy::fTOTAL_ENEMIES_PER_SCENE = 50;
	Enemy::fSPAWNED_ENEMIES_PER_SCENE = 0;

	m_GameObjectManager = new GameObjectManager();
	m_roadManager = new RoadManager();
	m_roadManager->Generate();

	for(int x = 0; x < m_roadManager->m_iGridSizeX; x++)
	{
		for(int y = 0; y < m_roadManager->m_iGridSizeY; y++)
		{
			if(m_roadManager->roadPieces[x][y]->GetName() == "field_grass")
			{
				sf::IntRect rect(
					m_roadManager->roadPieces[x][y]->getPosition().x - m_roadManager->roadPieces[x][y]->getTextureRect().width / 2,
					m_roadManager->roadPieces[x][y]->getPosition().y - m_roadManager->roadPieces[x][y]->getTextureRect().height / 2, 
					m_roadManager->roadPieces[x][y]->getTextureRect().width,
					m_roadManager->roadPieces[x][y]->getTextureRect().height
				);
				RandomlyPlaceObjects("tree", 20, rect);
			}
		}
	}

	for(int i = 0; i < 10; i++)
	{
		Medipack* medipack = new Medipack();
		float x = -512 * ((m_roadManager->m_iGridSizeX - 2) / 2) + MathHelper::Random() * (m_roadManager->m_iGridSizeX - 4);
		float y = -768 * ((m_roadManager->m_iGridSizeY - 2) / 2) + MathHelper::Random() * (m_roadManager->m_iGridSizeY - 4);

		medipack->setPosition(x, y);
		m_GameObjectManager->Add(medipack);
	}
	for(int i = 0; i < 6; i++)
	{
		GameObject* barrel = new GameObject("barrel");
		
		barrel->move(100 + i * 100.0f, -30 + (i%2 * 100));
		m_GameObjectManager->Add(barrel);
	}

	GameObject* pond = new GameObject("pond");
	pond->move(-400, 400);
	m_GameObjectManager->Add(pond);

	m_font = new sf::Font();
	m_font->loadFromFile("D:/Dropbox/NHTV/Intake/BurstinBubbles/BurstinBubbles/Data/Fonts/defused.ttf");

	m_lifebarText.setString("Health");
	m_lifebarText.move(20,0);
	m_lifebarText.setFont(*m_font);
	m_lifebarText.setCharacterSize(16);
	m_lifebarText.setColor(sf::Color::Black);

	std::string temp = "Starting";
	m_killText.setString(temp);

	m_killText.setPosition(SCREEN_WIDTH - m_skull.getTextureRect().width - 180, 0);
	m_killText.setFont(*m_font);
	m_killText.setCharacterSize(24);
	m_killText.setColor(sf::Color::Black);

	m_bCameraFollowsPlayer = true;
	m_bPlayerIsDead = false;

	m_lifeBar.setTexture(*TextureManager::getInstance()->m_Textures["lifebar"]);
	m_lifeBar.setPosition(20,20);
	m_lifeBar.setScale(1.0f,1);
	m_lifeBarRed.setTexture(*TextureManager::getInstance()->m_Textures["lifebarred"]);
	m_lifeBarRed.setPosition(20,20);
	m_lifeBarRed.setScale(1.0f,1);
	
	m_bScenePlaying = true;
}


Scene::~Scene(void)
{
	delete m_GameObjectManager;
}


void Scene::Update(float fDeltaTime)
{
	if(m_bScenePlaying)
	{
		m_GameObjectManager->Update(fDeltaTime);
		if(m_bCameraFollowsPlayer)
		{
			m_roadManager->AlignToPlayer(m_GameObjectManager->m_player);
			m_GameObjectManager->CenterPlayer();
		}
	}
	if(m_GameObjectManager->m_player->m_bIsDead || Enemy::fCurrentEnemies == 0)
	{
		m_bPlayerIsDead = true;
	}
}


void Scene::Draw(sf::RenderWindow *window)
{
	m_roadManager->Draw(window);
	m_GameObjectManager->Draw(window);
	
	window->draw(m_lifeBarRed);
	m_lifeBar.setTextureRect(sf::IntRect(0,0, (m_GameObjectManager->m_player->m_fHealth / 100) * m_lifeBarRed.getTextureRect().width,m_lifeBarRed.getTextureRect().height));
	window->draw(m_lifeBar);
	window->draw(m_lifebarText);
	int killText = Enemy::fCurrentEnemies + (Enemy::fTOTAL_ENEMIES_PER_SCENE - Enemy::fSPAWNED_ENEMIES_PER_SCENE);
	char temp[256];
	sprintf(temp, "%d enemies left", killText);
	m_killText.setString(temp);
	window->draw(m_killText);

}


void Scene::LoadFromFile(std::string sFile)
{
	/*
	 *	TODO: Implement loading of .scene-file. Placing assets, players, enemies, etc through GameObjectManager.
	 */
}


void Scene::RandomlyPlaceObjects(std::string name, int amount, sf::IntRect range)
{
	for(int i = 0; i < amount; i++)
	{
		GameObject* go = new GameObject(name);
		go->setPosition(range.left + range.width * MathHelper::Random(), range.top + range.height * MathHelper::Random());
		m_GameObjectManager->Add(go);
	}
}