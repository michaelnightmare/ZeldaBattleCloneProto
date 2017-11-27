#include "SwordSwipe.h"
#include "Game.h"
#include "GameObjects.h"
#include <iostream> 

SwordSwipe::SwordSwipe(sf::Vector2f pos, sf::Vector2f size)
	: GameObject(" ", pos, size, sf::RectangleShape(size))
	, m_timeAlive(0.0f)
	, SwipeSpeed(50.0F)
{
	body.setFillColor(sf::Color::Transparent);
}

void SwordSwipe::Update(sf::RenderWindow * window, float dt)
{
	std::cout << m_owner->m_Ehealth << std::endl;
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
		
		sf::RectangleShape lastEnemyPosition = enemy->GetLastFrameCollision();

		if (lastEnemyPosition.getPosition().y + lastEnemyPosition.getSize().y > m_collision.getPosition().y &&
			(lastEnemyPosition.getPosition().y < (lastEnemyPosition.getPosition().y + m_lastCollision.getSize().y)))

		{
			m_owner->m_Ehealth--;
			enemy->m_pos.y += 50;


			if (m_owner->m_Ehealth <= 0)
			{
				Destroy();
				other->Destroy();
			}
		}
		if (lastEnemyPosition.getPosition().y + lastEnemyPosition.getSize().y < m_collision.getPosition().y &&
			(lastEnemyPosition.getPosition().y > (lastEnemyPosition.getPosition().y + m_lastCollision.getSize().y)))

		{
			m_owner->m_Ehealth--;
			enemy->m_pos.y -= 50;


			if (m_owner->m_Ehealth <= 0)
			{
				Destroy();
				other->Destroy();
			}
		}
		 if (lastEnemyPosition.getPosition().x + lastEnemyPosition.getSize().x < m_collision.getPosition().x &&
			(lastEnemyPosition.getPosition().x >(lastEnemyPosition.getPosition().x + m_lastCollision.getSize().x)))

		{
			m_owner->m_Ehealth--;
			enemy->m_pos.x -= 50;


			if (m_owner->m_Ehealth <= 0)
			{
				Destroy();
				other->Destroy();
			}
		}
		 if (lastEnemyPosition.getPosition().x + lastEnemyPosition.getSize().x < m_collision.getPosition().x &&
			 (lastEnemyPosition.getPosition().x < (lastEnemyPosition.getPosition().x + m_lastCollision.getSize().x)))

		 {
			 m_owner->m_Ehealth--;
			 enemy->m_pos.x += 50;


			 if (m_owner->m_Ehealth <= 0)
			 {
				 Destroy();
				 other->Destroy();
			 }
		 }
	}

}

