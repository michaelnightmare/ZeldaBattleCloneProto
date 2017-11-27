#include "Player.h"
#include "Game.h"
#include "GameObjects.h"
#include <iostream>
#include "Animator.h"
#include "Approach.h"
#include "Collider.h"
#include "SwordSwipe.h"


Player::Player(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(sf::Vector2f(50, 150)))
	, playerSpeed(0.f)
	, playerSpeedUD(0.0f)
	, facingRight(false)
	, facingLeft(false)
	, facingUp(false)
	, facingDown(true)
	, enemyIsDead(false)
	, attacking(false)
	, SwipeSpeed(10.0f)
	
{   

	anim = new Animator(this);
	m_collision.setSize(sf::Vector2f(37.f,55.f));
	
	BumpSound.setBuffer(BumpBuffer);
	if (!BumpBuffer.loadFromFile("Audio/Bump.wav"))
	{
		std::cout << "error";
	}
	//left and right speed
	maxSpeed = 300.f;
	currentAcceleration = 0.f;
	defaultAcceleration = 500.f;
	defaultDeceleration = 3000.f;
	//up and down speed
	maxSpeedUD = 300.f;
	currentAccelerationUD = 0.f;
	defaultAccelerationUD = 200.f;
	defaultDecelerationUD = 3000.f;
	
}

void Player::Update(sf::RenderWindow * window, float dt)
{
	
	m_owner->m_invulnerable -= dt;
	m_owner->m_knockbacktimer -= dt; 

	if (m_owner->m_knockbacktimer <= 0.0f)
	{
		m_vel.y = 0.f;
		m_vel.x = 0.f;

	}


	//Restrain();

	//Check for movement commands
	//Start by zeroing out m_movement
	m_movement.x = 0.f;
	m_movement.y = 0.f;

	//Check for input and apply movement etc..
	HandleInput(dt);
	
	//Add acceleration to velocity, then add the velocity to movement
	m_movement += m_vel * dt; 
	
	//Add any movement to the player
    m_pos.y += m_movement.y;
	m_pos.x += m_movement.x;

	//Update the animator
	anim->Update(window, dt);

	//Set the body to the new position	
	UpdateCollision();	
}

void Player::UpdateCollision()
{
	body.setPosition(m_pos);
	GameObject::Update(NULL, 0.0f);
	m_collision.setPosition(body.getSize().x * .25f + body.getPosition().x, body.getSize().y * .25f + body.getPosition().y);
}

void Player::CollidedWith(GameObject * other)
{
	
	//Platform Collision
	//------------------------------------------------------------
	Boarder* m_boarder = dynamic_cast<Boarder*>(other);

	bool collidedVertically = false;
	bool collidedHorizontally = false;
	if (m_boarder != nullptr )
	{				
		if (GetCollider().CheckCollision(other->GetCollider()))
		{				
			m_pos.y -= m_movement.y;
			m_vel.y = 0;
			isgrounded = true;
			UpdateCollision();
			collidedVertically = true;
		}
		if (GetCollider().CheckCollision(other->GetCollider()))
		{	
			m_pos.x -= m_movement.x;
			UpdateCollision();
			collidedHorizontally = true;
		}
	}

}

void Player::HandleInput(float dt)
{
	if (facingDown && !attacking)
	{
		anim->ChooseRow(AnimationType::IDLED);

	}
	else if (!facingDown && !facingUp && !facingRight && !attacking)
	{
		anim->ChooseRow(AnimationType::IDLEL);
	}
	else if (!facingDown && !facingUp && !facingLeft && !attacking)
	{
		anim->ChooseRow(AnimationType::IDLER);
	}
	else if (!facingDown && !facingRight && !facingLeft && !attacking)
	{
		anim->ChooseRow(AnimationType::IDLEU);
	}

	currentAcceleration = 0.f;
	currentAccelerationUD = 0.0f;
	//KEY PRESSED
	//---------------------------------------------
	
	//Movement to the right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
			attacking = false; 
			facingRight = true;
			facingDown = false;
			facingUp = false;
			facingLeft = false;
			currentAcceleration = defaultAcceleration;
			anim->ChooseRow(AnimationType::RUN);
		
	}
	//Movement to the left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
			attacking = false;
			facingRight = false;
			facingDown = false;
			facingUp = false;
			facingLeft = true;
			currentAcceleration = -defaultAcceleration;
			anim->ChooseRow(AnimationType::RUNL) ;
	}
	playerSpeed += currentAcceleration * dt;

	if (playerSpeed > maxSpeed)
	{
		playerSpeed = maxSpeed;
	}

	if (playerSpeed < -maxSpeed)
	{
		playerSpeed = -maxSpeed;
	}

	if (currentAcceleration == 0 && playerSpeed != 0)
	{
		playerSpeed -= playerSpeed * 20 * dt;
	}

	m_movement.x = playerSpeed * dt;

		//Movement Up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			attacking = false;
			facingRight = false;
			facingDown = false;
			facingUp = true;
			facingLeft = false;
			currentAccelerationUD = -defaultAccelerationUD;
			anim->ChooseRow(AnimationType::RUNU);

		}

			//Movement Down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				
				attacking = false;
				facingRight = false;
				facingDown = true;
				facingUp = false;
				facingLeft = false;
				currentAccelerationUD = defaultAccelerationUD;
				anim->ChooseRow(AnimationType::RUND);
			}

			playerSpeedUD += currentAccelerationUD  * dt;

			if (playerSpeedUD > maxSpeedUD)
			{
				playerSpeedUD = maxSpeedUD;
			}

			if (playerSpeedUD < -maxSpeedUD)
			{
				playerSpeedUD = -maxSpeedUD;
			}

			if (currentAccelerationUD == 0 && playerSpeedUD != 0)
			{
				playerSpeedUD -= playerSpeedUD * 20 * dt;
			}

			m_movement.y = playerSpeedUD * dt;
		
	
	//Movement ATTACK
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		attacking = true;
		if (facingDown)
		{
			anim->ChooseRow(AnimationType::SWINGD);
			SwordSwipe* swordSwipe = new SwordSwipe(sf::Vector2f(this->GetPosition().x + 10, this->GetPosition().y+70), sf::Vector2f(50, 35));
			swordSwipe->m_vel.y += swordSwipe->SwipeSpeed;
			m_owner->AddObject(swordSwipe);

		}
		else if (!facingDown && !facingUp && !facingRight)
		{
			anim->ChooseRow(AnimationType::SWINGL);
			SwordSwipe* swordSwipe = new SwordSwipe(sf::Vector2f(this->GetPosition().x + 7 , this->GetPosition().y), sf::Vector2f(15, 80));
			swordSwipe->m_vel.x += swordSwipe->SwipeSpeed;
			m_owner->AddObject(swordSwipe);

		}
		else if (!facingDown && !facingUp && !facingLeft)
		{
			anim->ChooseRow(AnimationType::SWINGR);
			SwordSwipe* swordSwipe = new SwordSwipe(sf::Vector2f(this->GetPosition().x +50, this->GetPosition().y), sf::Vector2f(15, 80));
			swordSwipe->m_vel.x += swordSwipe->SwipeSpeed;
			m_owner->AddObject(swordSwipe);
		}
		else if (!facingDown && !facingRight && !facingLeft)
		{
			anim->ChooseRow(AnimationType::SWINGU);
			SwordSwipe* swordSwipe = new SwordSwipe(sf::Vector2f(this->GetPosition().x + 10, this->GetPosition().y), sf::Vector2f(50, 25));
			swordSwipe->m_vel.y += swordSwipe->SwipeSpeed;
			m_owner->AddObject(swordSwipe);
		}
		
	}
	attacking = false; 

}


void Player::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
}

