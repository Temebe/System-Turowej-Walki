// System Turowej Walki.cpp : Defines the entry point for the console application.
//

//System walki turowej
//Autor: Sebastian Aksamit
//https://kenney.nl/assets

#include "stdafx.h"
#include "Unit.h"
#include "InterfaceButton.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window{ VideoMode {800, 600}, "System Turowej Walki" };
	window.setFramerateLimit(60);
	Event event;
	Mouse mouse;
	Event::MouseWheelScrollEvent wheelEvent;
	Knight knight;
	InterfaceButton newGame, loadGame, options, exit;
	newGame.setTextureImage("include/buttons/newgame.png");
	newGame.setPosition(310, 300);
	loadGame.setTextureImage("include/buttons/loadgame.png");
	loadGame.setPosition(310, 350);
	options.setTextureImage("include/buttons/options.png");
	options.setPosition(310, 400);
	exit.setTextureImage("include/buttons/exit.png");
	exit.setPosition(310, 450);
	int i = 0, j=0;
	double k = 1;
	while (true) {
		window.clear(Color::Black);
		window.draw(knight);
		window.draw(newGame);
		window.draw(loadGame);
		window.draw(options);
		window.draw(exit);
		window.pollEvent(event);
		if (event.type == Event::Closed) {
			window.close();
			break;
		}
		if (event.type == Event::MouseButtonPressed) {
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 300) // NEW GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 345)) {
				cout << "New game" << endl;
			}
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 350) // LOAD GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 395)) {
				cout << "Load game" << endl;
			}
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 400) // OPTIONS GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 445)) {
				cout << "Options" << endl;
			}
			if ((mouse.getPosition(window).x > 310) && (mouse.getPosition(window).y > 450) // EXIT GAME
				&& (mouse.getPosition(window).x < 490) && (mouse.getPosition(window).y < 495)) {
				cout << "Exit" << endl;
				break;
			}
			/*if (mouse.getPosition(window).x > i) i+=5;
			else i-=5;
			if (mouse.getPosition(window).y > j) j+=5;
			else j-=5;
			knight.setPosition(i, j);
			cout << i << " " << j << " " << mouse.getPosition(window).x << " " << mouse.getPosition(window).y << endl;*/
		}
		if (event.type == Event::MouseWheelScrolled) {
			cout << event.mouseWheel.delta << endl;
			if (event.mouseWheel.delta > 0) k = 1;
			else k = -1;
			knight.setScale(k, k);
			cout << k << endl;
		}
		window.display();
	}
    return 0;
}

