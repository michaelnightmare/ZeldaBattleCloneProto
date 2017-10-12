#include "Boss.h"
#include <iostream>
#include "Animator.h"
#include "GameObjects.h"
#include "Game.h"


Boss::Boss(std::string texturePath, sf::Vector2f pos, sf::Vector2f size, Ship* player)
	: GameObject(texturePath, pos, size, sf::RectangleShape(size))
	, bossAlive(true)
	, bossPStart(0, m_pos.y)
	, bossPEnd(0, m_pos.y - 125)
	, patrolTimer(2.f)
	, bossDead(false)



{
	body.setSize(m_size/2.f);
	//m_collision.setSize(m_size / 2.f);

	anim = new Animator(this);

	
	movementFrame = bossPEnd - bossPStart;
	//m_stateMachine->SetCurrentState(StandingState::Instance());

	PlayerHurtSound.setBuffer(PlayerHurtBuffer);
	if (!PlayerHurtBuffer.loadFromFile("Audio/PlayerHurt.wav"))
	{
		std::cout << "error";
	}
	
}



void Boss::Update(sf::RenderWindow * window, float dt)
{
	

	Patrol(dt);

	body.setPosition(m_pos);

	GameObject::Update(window, dt);

}

void Boss::CollidedWith(GameObject * other)
{



}

void Boss::Patrol(float dt)
{
	if (bossAlive)
	{
		patrolTimer -= dt;

		if (patrolTimer <= 0.f)
		{
			movementFrame.y *= -1;
			patrolTimer = 2.f;

		
		}

		m_pos.y += movementFrame.y *dt;
	}
	else
	{

	}
}


void Boss::Destroy()
{
	GameObject::Destroy();

}

void Boss::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);

}

