#include "stdafx.h"
#include "BattlegroundScene.h"


int BattlegroundScene::render(sf::RenderWindow & window, Save& save, bool& loaded)
{
	mouseHold = false;
	//test
	//teamA = save.getTeamA();
	//teamB = save.getTeamB();
	std::cout << "Knights from team A: " << save.getTeamA().at(0) << std::endl;
	std::cout << "Warriors from team A: " << save.getTeamA().at(1) << std::endl;
	std::cout << "Archers from team A: " << save.getTeamA().at(2) << std::endl;
	std::cout << "Riders from team A: " << save.getTeamA().at(3) << std::endl;
	std::cout << "Mages from team A: " << save.getTeamA().at(4) << std::endl;
	std::cout << "Knights from team B: " << save.getTeamB().at(0) << std::endl;
	std::cout << "Warriors from team B: " << save.getTeamB().at(1) << std::endl;
	std::cout << "Archers from team B: " << save.getTeamB().at(2) << std::endl;
	std::cout << "Riders from team B: " << save.getTeamB().at(3) << std::endl;
	std::cout << "Mages from team B: " << save.getTeamB().at(4) << std::endl;
	if (loaded != true) {
		std::cout << "TO ROBIE" << std::endl;
		for (unsigned int i = 0; i < save.getMapSize(); i++) {
			for (unsigned int j = 0; j < save.getMapSize(); j++) {
				std::cout << i << " " << j << std::endl;
				if ((i == 0) && (j == 0)) {
					std::cout << "1 for" << std::endl;
					first = new Square;
					first->setTexture(mapTile);
					std::cout << "1 for koniec" << std::endl;
				}
				else if ((i == 0) && (j == 1)){
					std::cout << "2 for" << std::endl;
					prev = new Square;
					prev->setTexture(mapTile);
					first->setRight(prev);
					prev->setLeft(first);
					std::cout << "2 for koniec" << std::endl;
				}
				else if ((i == 0) && (j > 1)) {
					std::cout << "3 for" << std::endl;
					temp = new Square;
					temp->setTexture(mapTile);
					temp->setLeft(prev);
					prev->setRight(temp);
					prev = temp;
					std::cout << "3 for koniec" << std::endl;
				}
				else if ((i > 0) && (j == 0)) {
					std::cout << "4 for" << std::endl;
					prev = new Square;
					prev->setTexture(mapTile);
					temp = first;
					for (unsigned int k = 1; k < i; k++) {
						std::cout << "Poink!" << std::endl;
						temp = temp->getDown();
					}
					if (temp == nullptr) std::cout << "temp jest nullptr" << std::endl;
					temp->setDown(prev);
					prev->setUp(temp);
					std::cout << "4 for koniec" << std::endl;
				}
				else {
					std::cout << "5 for" << std::endl;
					temp = new Square;
					temp->setTexture(mapTile);
					temp->setLeft(prev);
					prev->setRight(temp);
					if (prev == nullptr) std::cout << "prev jest nullptr" << std::endl;
					if (prev->getUp() == nullptr) std::cout << "prev->getUp() jest nullptr" << std::endl;
					if (prev->getUp()->getRight() == nullptr) std::cout << "prev->getUp()->getRight() jest nullptr" << std::endl;
					temp->setUp(prev->getUp()->getRight());
					temp->getUp()->setDown(temp);
					std::cout << "5 for koniec" << std::endl;
				}
			}
		}
		temp = nullptr;
		prev = nullptr;
	}
	while (true) {
		window.clear(sf::Color::Black);
		window.pollEvent(event);
		temp = first;
		std::cout << "TUTAJ" << std::endl;
		for (unsigned int i = 0; i < save.getMapSize(); i++) {
			for (unsigned int j = 0; j < save.getMapSize()-1; j++) {
				window.draw(*temp);
				temp = temp->getRight();
			}
			temp = first;
			for (unsigned int j = 1; j < i; j++) {
				temp = temp->getDown();
			}
		}
		if ((event.type == sf::Event::MouseButtonPressed) && (mouseHold != true)) {
			mouseHold = true;
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
		}
		window.display();
	}
}

BattlegroundScene::BattlegroundScene()
{
	mapTile.loadFromFile("include/images/mapTile.png");
	mapTileTouched.loadFromFile("include/images/mapTileTouched.png");
	temp = nullptr;
	prev = nullptr;
}


BattlegroundScene::~BattlegroundScene()
{
}
