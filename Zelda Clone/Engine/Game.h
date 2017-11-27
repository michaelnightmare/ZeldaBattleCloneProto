#pragma once
#include "GameObjects.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Boarder.h"
#include "Collectible.h"
#include "NonInteractive.h"
#include "Levelhazards.h"
#include "Boss.h"




class Game
{
public:
	Game();

	void Update(sf::RenderWindow* window, float dt);
	void Draw(sf::RenderWindow* window);
	void AddObject(GameObject* obj);
	std::vector<GameObject*> m_gameObjects;
	void RespawnPlayer();
	void ToggleDrawCollision() {m_drawCollision = !m_drawCollision;}
	bool DrawCollision() { return m_drawCollision;  }
	int m_healthRemaining;
	int m_Ehealth;
	int m_bossHealthRemaining;
	float m_invulnerable;
	float m_Einvulnerable;
	float m_knockbacktimer;

private:
	Player* m_player;
	Boarder* m_boarder;
	sf::View* playerView;
	Enemy* m_enemy;
	Collectible* m_collectible;
	NonInteractive* m_noninteractive;
	LevelHazards* m_levelhazards;
	Boss* m_boss;

	sf::Font m_mainFont;
	bool m_gameOver;
	
	int m_livesRemaining;
	float m_timeUntilRespawn;
	bool m_win;
	bool m_drawCollision;

	
};

