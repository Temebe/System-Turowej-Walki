#include "stdafx.h"
#include "MenuScene.h"


MenuScene::MenuScene()
{
	test.setFont(font);
	test.setString("System walki turowej");
	test.setFillColor(sf::Color::Red);
	test.setPosition(200, 200);
	version.setFont(font);
	version.setString("alpha 1.2");
	version.setPosition(900, 750);
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

int MenuScene::render(sf::RenderWindow& window, Save& save)
{
	while (true) {
		window.clear(sf::Color::Black);
		window.draw(newGame);
		window.draw(loadGame);
		window.draw(options);
		window.draw(exit);
		window.draw(test);
		window.draw(version);
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			return 5;
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if(newGame.isMouseOver(mouse, window)) {
				std::cout << "New game" << std::endl;
				return 3;
			}
			if (loadGame.isMouseOver(mouse, window)) {
				std::cout << "Load game" << std::endl;
				save.setLoadingMode(true);
				return 4;
			}
			if (options.isMouseOver(mouse, window)) {
				std::cout << "Options" << std::endl;
				return 1;
			}
			if (exit.isMouseOver(mouse, window)) {
				std::cout << "Exit" << std::endl;
				return 5;
			}
		}
		window.display();
	}
}
