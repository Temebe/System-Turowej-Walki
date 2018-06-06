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
	optionTitle.setFont(font);
	optionTitle.setPosition(100, 50);
	optionTitle.setString("Volume: ");
	returnButton.setTextureImage("include/buttons/return.png");
	returnButton.setPosition(800, 700);
	thanks.setFont(font);
	thanks.setPosition(100, 300);
	thanks.setString("Special thanks to:\nkenney.nl for most of graphic assets used\ndabuttonfactory.com for buttons\n\nMusic:\nDoctor Turtle - The Ants Built A City On His Chest\n\nAll used content is public domain");
}


OptionsMenu::~OptionsMenu()
{
}

int OptionsMenu::render(sf::RenderWindow& window, sf::Music& music)
{
	mouseHold = false;
	while (true) {
		window.clear(sf::Color(120, 145, 205));
		window.draw(volUp);
		window.draw(volDn);
		window.draw(volText);
		window.draw(optionTitle);
		window.draw(thanks);
		window.draw(returnButton);
		window.pollEvent(event);
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				return 5;
			}
		}
		if ((event.type == sf::Event::MouseButtonPressed) && (mouseHold != true)) {
			mouseHold = true;
			if (volUp.isMouseOver(mouse, window)) {
				music.setVolume(round(music.getVolume() + 1));
				volText.setString(std::to_string((int) music.getVolume()));
			}
			if (volDn.isMouseOver(mouse, window)) {
				music.setVolume(round(music.getVolume() - 1));
				volText.setString(std::to_string((int) music.getVolume()));
			}
			if (returnButton.isMouseOver(mouse, window)) return 0;
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
		}
		window.display();
	}
}
