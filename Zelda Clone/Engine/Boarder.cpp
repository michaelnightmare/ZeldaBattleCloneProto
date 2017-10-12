#include "Game.h"
#include "GameObjects.h"
#include "Boarder.h"




Boarder::Boarder(sf::Vector2f pos,sf::Vector2f size)
	: GameObject("", pos, size, sf::RectangleShape(size))

{

	body.setSize(m_size/ 2.0f );
	body.setFillColor(sf::Color::Transparent);
	m_collision.setSize(m_size / 2.0f);


}



void Boarder::Update(sf::RenderWindow * window, float dt)
{
	GameObject::Update(window, dt);
}

void Boarder::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(body);
}