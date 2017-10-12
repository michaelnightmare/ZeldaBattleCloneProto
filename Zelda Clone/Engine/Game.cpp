#include "Game.h"
#include <iostream>
#include "SFML\Graphics.hpp"
#include "GameObjects.h"
#include "Collider.h"
#include "Player.h"
#include <sstream>
#include "Enemy.h"


Game::Game()
	: m_gameOver(false)
	, m_timeUntilRespawn(.01f)
	, m_livesRemaining(2)
	, m_invulnerable(1.0f)
	, m_healthRemaining(4)
	, m_drawCollision(false)
	, m_bossHealthRemaining(10)
	, m_win(false)
	
{ 
	m_mainFont.loadFromFile("Fonts/kenpixel_high_square.ttf");

//Player
	m_player = new Player("Sprites/PNG/PNW.png", sf::Vector2f(0, 0), sf::Vector2f (200,150));
//enemy
	m_enemy = new Enemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(1000, 2200), sf::Vector2f(150, 150));
	AddObject(m_enemy);

//level boardering 
	//near player start
	m_boarder = new Boarder(sf::Vector2f(850, 2975), sf::Vector2f(400, 1));
	AddObject(m_boarder);

	//below player start (bottom part of level)
	m_boarder = new Boarder(sf::Vector2f(1150, 2840), sf::Vector2f(1000, 1));
	AddObject(m_boarder);

	m_boarder = new Boarder(sf::Vector2f(1700, 2975), sf::Vector2f(1600, 1));
	AddObject(m_boarder);

	m_boarder = new Boarder(sf::Vector2f(2600, 2890), sf::Vector2f(1000, 1));
	AddObject(m_boarder);

	//filler
	m_boarder = new Boarder(sf::Vector2f(1075, 2910), sf::Vector2f(1250, 40));
	AddObject(m_boarder);

	m_boarder = new Boarder(sf::Vector2f(2530, 2950), sf::Vector2f(1000, 40));
	AddObject(m_boarder);

	//near walkway
	m_boarder = new Boarder(sf::Vector2f(2570, 2910), sf::Vector2f(1000, 40));
	AddObject(m_boarder);

	m_boarder = new Boarder(sf::Vector2f(2530, 2950), sf::Vector2f(1000, 40));
	AddObject(m_boarder);


	m_boarder = new Boarder(sf::Vector2f(900, 1820), sf::Vector2f(10000, 1));
	AddObject(m_boarder);

	//right wall
	m_boarder = new Boarder(sf::Vector2f(2500, 10), sf::Vector2f(20, 10000));
	AddObject(m_boarder);
	//left wall
	m_boarder = new Boarder(sf::Vector2f(900, 10), sf::Vector2f(20, 10000));
	AddObject(m_boarder);



//Player View
	playerView = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(720.0f, 720.0f));



}

void Game::Update(sf::RenderWindow * window, float dt)
{


	//ReSpawn Timer
	if (m_timeUntilRespawn > 0)
	{
		m_timeUntilRespawn -= dt;
		if (m_timeUntilRespawn <= 0)
		{
			
				m_player = new Player("Sprites/PNG/PNWD.png", sf::Vector2f(1000, 1900), sf::Vector2f(75, 100));
				AddObject(m_player);
		
		}
	}

	//Destroy loop
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		if (current->IsDestroyed())
		{
			delete current;
			m_gameObjects.erase(m_gameObjects.begin() + i);
		}
	}

	//Update loop
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		current->Update(window, dt);
	}

	//Collision Loop
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		for (int j = 0; j < m_gameObjects.size(); j++)
		{
			GameObject* other = m_gameObjects[j];
			if (current->GetCollider().CheckCollision(other->GetCollider()))
			{
				current->CollidedWith(other);
			}
		}
	}

}

void Game::Draw(sf::RenderWindow * window)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		current->Draw(window);
	}

	//HUD

	//Hero Health Hearts
	for (int i = 0; i < m_healthRemaining; i++)
	{

		sf::Texture texture4;
		if (!texture4.loadFromFile("Sprites/PNG/Heart_full.png"))
		{
			std::cout << "texture wont load";
		}
		sf::Sprite Heart_full;
		Heart_full.setTexture(texture4);
		Heart_full.setScale(.25, .25);
		Heart_full.setPosition(playerView->getCenter() + sf::Vector2f(-335 + i * 25, -295));
		window->draw(Heart_full);

	}
	
	//GAME OVER TEXT
	if (m_gameOver)
	{
		sf::Text gameOverText;
		gameOverText.setFont(m_mainFont);
		gameOverText.setString("GAME OVER!");
		gameOverText.setCharacterSize(50);
		gameOverText.setPosition(900, 800);
		window->draw(gameOverText);
		m_healthRemaining = 0;
		m_livesRemaining = 0;
	
	}

	

	// if player is out of the ship view follows him	
	playerView->setCenter(m_player->GetPosition().x+50, m_player->GetPosition().y);
	//If player is at edge, keep screen from showing black space
	if (m_player->GetPosition().x > 3075.f)
	{
		playerView->setCenter(m_player->GetPosition().x, m_player->GetPosition().y);
	}
	
	if (m_player->GetPosition().y > 2600.f)
	{
		playerView->setCenter(m_player->GetPosition().x, m_player->GetPosition().y-180);
	}
	

	//if player wins the screen shifts to this location
	if ( m_gameOver)
	{
		playerView->setCenter(2000, 2000);
	}

	window->setView(*playerView);
}

void Game::AddObject(GameObject * obj)
{
	m_gameObjects.push_back(obj);
	obj->SetOwner(this);
}

void Game::RespawnPlayer()
{
	if (m_livesRemaining > 0)
	{
		m_livesRemaining--;
		m_timeUntilRespawn = 1.0f;
		m_healthRemaining = 4;
	

	}

	else
	{
		m_gameOver = true;
		
	}

}









