#include "stdafx.h"
#include "BattlegroundScene.h"


int BattlegroundScene::render(sf::RenderWindow & window, Save& save, bool& loaded)
{
	mouseHold = false;
	//test
	//teamA = save.getTeamA();
	//teamB = save.getTeamB();
	/*std::cout << "Knights from team A: " << save.getTeamA().at(0) << std::endl;
	std::cout << "Warriors from team A: " << save.getTeamA().at(1) << std::endl;
	std::cout << "Archers from team A: " << save.getTeamA().at(2) << std::endl;
	std::cout << "Riders from team A: " << save.getTeamA().at(3) << std::endl;
	std::cout << "Mages from team A: " << save.getTeamA().at(4) << std::endl;
	std::cout << "Knights from team B: " << save.getTeamB().at(0) << std::endl;
	std::cout << "Warriors from team B: " << save.getTeamB().at(1) << std::endl;
	std::cout << "Archers from team B: " << save.getTeamB().at(2) << std::endl;
	std::cout << "Riders from team B: " << save.getTeamB().at(3) << std::endl;
	std::cout << "Mages from team B: " << save.getTeamB().at(4) << std::endl;*/
	if (loaded != true) {
		std::cout << "TO ROBIE" << std::endl;
		for (unsigned int i = 0; i < save.getMapSize(); i++) {
			for (unsigned int j = 0; j < save.getMapSize(); j++) {
				std::cout << i << " " << j << std::endl;
				if ((i == 0) && (j == 0)) {
					first = new Square;
					first->setTexture(mapTile);
					first->setPosition(0, 0);
				}
				else if ((i == 0) && (j == 1)){
					prev = new Square;
					prev->setTexture(mapTile);
					prev->setPosition(64, 0);
					first->setRight(prev);
					prev->setLeft(first);
				}
				else if ((i == 0) && (j > 1)) {
					temp = new Square;
					temp->setTexture(mapTile);
					temp->setPosition((float)j*64, 0);
					temp->setLeft(prev);
					prev->setRight(temp);
					prev = temp;
				}
				else if ((i > 0) && (j == 0)) {
					prev = new Square;
					prev->setTexture(mapTile);
					prev->setPosition((float)j * 64, (float)i * 64);
					temp = first;
					for (unsigned int k = 1; k < i; k++) {
						temp = temp->getDown();
					}
					temp->setDown(prev);
					prev->setUp(temp);
				}
				else {
					temp = new Square;
					temp->setTexture(mapTile);
					temp->setPosition((float)j * 64, (float)i * 64);
					temp->setLeft(prev);
					prev->setRight(temp);
					temp->setUp(prev->getUp()->getRight());
					temp->getUp()->setDown(temp);
					prev = temp;
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
		for (unsigned int i = 0; i < save.getMapSize(); i++) {
			for (unsigned int j = 0; j < save.getMapSize(); j++) {
				window.draw(*temp);
				temp = temp->getRight();
			}
			temp = first;
			for (unsigned int j = 0; j < i+1; j++) {
				temp = temp->getDown();
			}
		}
		if ((event.type == sf::Event::MouseButtonPressed) && (mouseHold != true)) {
			temp = first;
			nullSquare = false;
			for (int i = 0; i < mouse.getPosition(window).x / 64; i++) {
				if (temp->getRight() == nullptr) {
					nullSquare = true;
					break;
				}
				temp = temp->getRight();
			}
			for (int i = 0; i < mouse.getPosition(window).y / 64; i++) {
				if ((temp->getDown() == nullptr) || (nullSquare)) {
					nullSquare = true;
					break;
				}
				temp = temp->getDown();
			}
			if (!nullSquare) {
				if (actual == nullptr) {
					actual = temp;
					temp->touch();
					temp->setTexture(mapTileTouched);
				}
				else {
					if (actual == temp) {
						temp->touch();
						temp->setTexture(mapTile);
						actual = nullptr;
					}
					else {
						temp->touch();
						temp->setTexture(mapTileTouched);
						actual->touch();
						actual->setTexture(mapTile);
						actual = temp;
					}
				}
				/*if (temp->isTouched() == false) {
					temp->setTexture(mapTileTouched);
				}
				else {
					temp->setTexture(mapTile);
				}
				temp->touch();
				if ((actual != temp) && (actual != nullptr)) {

				}*/
			}
			//std::cout << mouse.getPosition(window).x << " " << mouse.getPosition(window).y << std::endl;
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
	actual = nullptr;
}


BattlegroundScene::~BattlegroundScene()
{
}
