#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	window.create(sf::VideoMode{ 1024, 800 }, "System Turowej Walki", sf::Style::Close);
	window.setFramerateLimit(60);
	actualScene = 0;
	music.openFromFile("include/music/music.ogg");
	music.setVolume(10);
	music.setLoop(true);
	music.play();
	loaded = false;
	view = window.getDefaultView();
	window.setView(view);
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
			actualScene = menuScene.render(window, save);
			break;
		case 1: //options
			std::cout << actualScene << std::endl;
			actualScene = optionsScene.render(window, music);
			break;
		case 2: //load game
			std::cout << actualScene << std::endl;
			actualScene = 0;
			break;
		case 3: //team select
			std::cout << actualScene << std::endl;
			actualScene = selectScene.render(window, save);
			break;
		case 4: //battleground
			std::cout << actualScene << std::endl;
			actualScene = battlegroundScene.render(window, save, view);
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
