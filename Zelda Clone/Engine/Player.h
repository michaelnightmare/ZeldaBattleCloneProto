#pragma once
#include "GameObjects.h"
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>


class Animator;
class StateMachine;

class Player : public GameObject
{
public:

	Player(std::string texturePath,  sf::Vector2f pos, sf::Vector2f size);
	void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	virtual void CollidedWith(GameObject* other);
	bool IsGrounded() { return isgrounded; }
	Collider GetCollider() { return Collider(body); }
	void HandleInput(float dt);
	void UpdateCollision();
	sf::SoundBuffer JumpBuffer;
	sf::Sound JumpSound;
	sf::SoundBuffer BumpBuffer;
	sf::Sound BumpSound;
	
	bool playerHit;
	
	
protected:

	Animator* anim;
	StateMachine* m_stateMachine;

	float currentAcceleration;
	float defaultAcceleration;
	float defaultDeceleration;
	float currentAccelerationUD;
	float defaultAccelerationUD;
	float defaultDecelerationUD;
	float playerSpeed;
	float maxSpeed;
	float playerSpeedUD;
	float maxSpeedUD;
	float SwipeSpeed;
	bool isjumping;
	bool isgrounded;
	bool facingRight;
	bool facingLeft;
	bool facingDown;
	bool facingUp;
	bool enemyIsDead;
	bool attacking;
	

	
	
	
};

