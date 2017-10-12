// Engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include "GameObjects.h"

int main()
{
	Game game;
	srand(static_cast<unsigned int>(time(0)));

	sf::RenderWindow window(sf::VideoMode(1000, 700), "Zelda Clone!");

	//Background Texture
	//-----------------------------------------------------
	sf::Texture texture;
	if (!texture.loadFromFile("Sprites/PNG/desert.png"))
	{
		std::cout << "texture wont load";
	}
	
	sf::Music Music;
	Music.openFromFile("Audio/Music.wav");
	//Music.play();
	Music.setLoop(true);
	Music.setVolume(20);
	
	sf::Sprite background;
	background.setTexture(texture);
	background.setScale(3, 3.f);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::C)
				{
					game.ToggleDrawCollision();
				}
			}
		}

		window.clear();
        window.draw(background);
		
		game.Update(&window, dt.asSeconds());
		game.Draw(&window);
		window.display();
	}

	return 0;
}
