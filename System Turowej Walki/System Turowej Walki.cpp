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
#include "MenuScene.h"

using namespace std;
using namespace sf;

int main()
{
	//RenderWindow window{ VideoMode {1024, 800}, "System Turowej Walki" };
	//window.setFramerateLimit(60);
	//Event event;
	Mouse mouse;
	//Event::MouseWheelScrollEvent wheelEvent;
	Knight knight;
	int i = 0, j=0;
	double k = 1;
	MenuScene menuScene;
	while (true) {
		menuScene.render();
	}
    return 0;
}

