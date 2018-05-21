#include "stdafx.h"
#include "MenuScene.h"


MenuScene::MenuScene()
{
	test.setFont(font);
	test.setString("TYTUL GRY");
	test.setFillColor(sf::Color::Red);
	test.setPosition(200, 200);
	newGame.setTextureImage("include/buttons/newgame.png");
	newGame.setPosition(310, 300);
	loadGame.setTextureImage("include/buttons/loadgame.png");
	loadGame.setPosition(310, 350);
	options.setTextureImage("include/buttons/options.png");
	options.setPosition(310, 400);
	exit.setTextureImage("include/buttons/exit.png");
	exit.setPosition(310, 450);
}


MenuScene::~MenuScene()
{
}

void MenuScene::render()
{
	while (true) {
		window.clear(sf::Color::Black);
		window.draw(knight);
		window.draw(newGame);
		window.draw(loadGame);
		window.draw(options);
		window.draw(exit);
		window.draw(test);
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			break;
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 300) // NEW GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 345)) {
				std::cout << "New game" << std::endl;
			}
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 350) // LOAD GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 395)) {
				std::cout << "Load game" << std::endl;
			}
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 400) // OPTIONS GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 445)) {
				std::cout << "Options" << std::endl;
			}
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 450) // EXIT GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 495)) {
				std::cout << "Exit" << std::endl;
				break;
			}
		}
		window.display();
	}
}
