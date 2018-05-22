#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	actualScene = 0;
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
			actualScene = menuScene.render();
			break;
		case 1: //options
			std::cout << actualScene << std::endl;
			actualScene = 5;
			break;
		case 2: //load game
			std::cout << actualScene << std::endl;
			actualScene = 5;
			break;
		case 3: //team select
			std::cout << actualScene << std::endl;
			actualScene = selectScene.render();
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
