#include "SwordSwipe.h"
#include "Game.h"
#include "GameObjects.h"
#include <iostream> 

SwordSwipe::SwordSwipe(sf::Vector2f pos, sf::Vector2f size)
	: GameObject(" ", pos, size, sf::RectangleShape(size))
	, m_timeAlive(0.0f)
	, SwipeSpeed(50.0F)
{
	body.setFillColor(sf::Color::Red);
}

void SwordSwipe::Update(sf::RenderWindow * window, float dt)
{

	m_pos.x += m_movement.x;
	m_movement += m_vel * dt;
	m_timeAlive += dt;

	if (m_timeAlive > .0002f)
	{
		Destroy();
	}
	body.setPosition(m_pos);
	GameObject::Update(window, dt);
}

void SwordSwipe::CollidedWith(GameObject * other)
{
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	if (enemy != nullptr)
	{



		Destroy();
		//enemyExplodeSound.play();
		other->Destroy();


	}

}

