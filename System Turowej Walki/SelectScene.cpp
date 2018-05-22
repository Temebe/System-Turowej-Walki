#include "stdafx.h"
#include "SelectScene.h"


int SelectScene::render()
{
	window.create(sf::VideoMode{ 1024, 800 }, "System Turowej Walki");
	while (true) {
		window.clear(sf::Color::Black);
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
				window.close();
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
