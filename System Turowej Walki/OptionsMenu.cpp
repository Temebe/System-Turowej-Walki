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
	volText.setString("10");
	returnButton.setTextureImage("include/buttons/return.png");
	returnButton.setPosition(800, 700);
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
		window.draw(returnButton);
		window.pollEvent(event);
		if ((event.type == sf::Event::MouseButtonPressed) && (mouseHold != true)) {
			mouseHold = true;
			if (volUp.isMouseOver(mouse, window)) {
				music.setVolume(round(music.getVolume() + 1));
				volText.setString(std::to_string(music.getVolume()));
			}
			if (volDn.isMouseOver(mouse, window)) {
				music.setVolume(round(music.getVolume() - 1));
				volText.setString(std::to_string(music.getVolume()));
			}
			if (returnButton.isMouseOver(mouse, window)) return 0;
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
		}
		window.display();
	}
}
