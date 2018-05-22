#include "stdafx.h"
#include "SelectScene.h"


int SelectScene::render()
{
	while (true) {
		window.clear(sf::Color::Black);
		std::cout << "select" << std::endl;
		window.draw(test);
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			return 5;
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 300) // do podmianki na inny przycisk
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 345)) {
				std::cout << "New game" << std::endl;
				return 3;
			}
		}
		window.display();
	}
}

SelectScene::SelectScene()
{
	test.setFont(font);
	test.setString("WYBIERZ JEDNOSTKI");
	test.setFillColor(sf::Color::Red);
	test.setPosition(200, 200);
}


SelectScene::~SelectScene()
{
}
