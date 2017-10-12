#include "Game.h"
#include "GameObjects.h"
#include "Levelhazards.h"
#include <iostream>




LevelHazards::LevelHazards(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(size))


{
	body.setSize(m_size / 4.0f);
	m_collision.setSize(m_size / 4.0f);


}

void LevelHazards::Update(sf::RenderWindow * window, float dt)
{
	GameObject::Update(window, dt);
	
}

void LevelHazards::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(body);
	
}

void LevelHazards::Destroy()
{
	GameObject::Destroy();
	
}

void LevelHazards::CollidedWith(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);

		player->Destroy();
		m_owner->RespawnPlayer();
}
