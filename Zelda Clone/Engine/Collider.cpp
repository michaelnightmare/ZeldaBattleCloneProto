#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) :
	body(body)
{
	Top = body.getPosition().y;

	Bottom = body.getPosition().y + body.getSize().y;

	Right = body.getPosition().x + body.getSize().x;

	Left = body.getPosition().x;
}


Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider & other)
{

	if ((other.Right > Left) &&

		(other.Left < Right) &&

		(other.Bottom > Top) &&

		(other.Top < Bottom))

	{

		return true;

	}

	return false;
}