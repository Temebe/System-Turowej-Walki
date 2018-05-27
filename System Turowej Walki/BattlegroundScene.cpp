#include "stdafx.h"
#include "BattlegroundScene.h"


int BattlegroundScene::render(sf::RenderWindow & window)
{
	mouseHold = false;
	while (true) {
		window.clear(sf::Color::Black);
		window.pollEvent(event);
		if ((event.type == sf::Event::MouseButtonPressed) && (mouseHold != true)) {
			mouseHold = true;
			/*if ((mouse.getPosition(window).x > 100) && (mouse.getPosition(window).y > 100)
				&& (mouse.getPosition(window).x < 130) && (mouse.getPosition(window).y < 130)) {
				music.setVolume(round(music.getVolume() + 1));
				volText.setString(std::to_string(music.getVolume()));
			}*/
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
		}
		window.display();
	}
}

BattlegroundScene::BattlegroundScene()
{
}


BattlegroundScene::~BattlegroundScene()
{
}
