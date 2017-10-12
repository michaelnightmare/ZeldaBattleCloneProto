#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy);}

	bool CheckCollision(Collider& other);
	//bool PushCollision(Collider& other, float push);
	sf::Vector2f GetPosition() {return body.getPosition(); }
	sf::Vector2f GetSize() { return body.getSize(); }
	sf::Vector2f GetHalfSize() { return body.getSize()/2.0f; }

	float Top;
	float Bottom;
	float Right;
	float Left;
	


private:
	sf::RectangleShape& body;
};