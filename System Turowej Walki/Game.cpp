#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	window.create(sf::VideoMode{ 1024, 800 }, "System Turowej Walki");
	window.setFramerateLimit(60);
	actualScene = 0;
	music.openFromFile("include/music/menu.ogg");
	music.setVolume(100);
	music.play();
}


Game::~Game()
{
}

void Game::run()
{
	while (true) {
		switch (actualScene) {
		case 0: //menu
			std::cout << actualScene << std::endl;
			actualScene = menuScene.render(window);
			break;
		case 1: //options
			std::cout << actualScene << std::endl;
			actualScene = optionsScene.render(window, music);
			break;
		case 2: //load game
			std::cout << actualScene << std::endl;
			actualScene = 5;
			break;
		case 3: //team select
			std::cout << actualScene << std::endl;
			actualScene = selectScene.render(window);
			break;
		case 4: //battleground
			std::cout << actualScene << std::endl;
			actualScene = 5;
			break;
		case 5: //exit
			std::cout << actualScene << std::endl;
			return;
		}
	}
}

void Game::setScene(int value)
{
	actualScene = value;
}
