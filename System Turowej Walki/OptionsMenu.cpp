#include "stdafx.h"
#include "OptionsMenu.h"
#include <math.h>


OptionsMenu::OptionsMenu()
{
	up.loadFromFile("include/buttons/+.png");
	dn.loadFromFile("include/buttons/-.png");
	volUp.setTexture(up);
	volDn.setTexture(dn);
	volUp.setPosition(100, 100);
	volDn.setPosition(200, 100);
	volText.setFont(font);
	volText.setPosition(150, 100);
	volText.setString("100");
}


OptionsMenu::~OptionsMenu()
{
}

int OptionsMenu::render(sf::RenderWindow& window, sf::Music& music)
{
	mouseHold = false;
	while (true) {
		window.clear(sf::Color::Black);
		window.draw(volUp);
		window.draw(volDn);
		window.draw(volText);
		window.pollEvent(event);
		if ((event.type == sf::Event::MouseButtonPressed) && (mouseHold != true)) {
			mouseHold = true;
			if ((mouse.getPosition(window).x > 100) && (mouse.getPosition(window).y > 100)
				&& (mouse.getPosition(window).x < 130) && (mouse.getPosition(window).y < 130)) {
				music.setVolume(round(music.getVolume() + 1));
				volText.setString(std::to_string(music.getVolume()));
			}
			if ((mouse.getPosition(window).x > 200) && (mouse.getPosition(window).y > 100)
				&& (mouse.getPosition(window).x < 230) && (mouse.getPosition(window).y < 130)) {
				music.setVolume(round(music.getVolume() - 1));
				volText.setString(std::to_string(music.getVolume()));
			}
			if ((mouse.getPosition(window).x > 500) && (mouse.getPosition(window).y > 500)
				&& (mouse.getPosition(window).x < 800) && (mouse.getPosition(window).y < 800)) {
				return 0;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
		}
		window.display();
	}
}
