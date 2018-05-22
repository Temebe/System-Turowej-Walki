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
		case 0:
			std::cout << "0" << std::endl;
			actualScene = menuScene.render();
			break;
		case 1:
			std::cout << "1" << std::endl;
			actualScene = selectScene.render();
			break;
		case 2:
			std::cout << "2" << std::endl;
			actualScene = 5;
			break;
		case 3:
			std::cout << "3" << std::endl;
			actualScene = 5;
			break;
		case 4:
			std::cout << "4" << std::endl;
			actualScene = 5;
			break;
		case 5:
			std::cout << "5" << std::endl;
			return;
		}
	}
}

void Game::setScene(int value)
{
	actualScene = value;
}
