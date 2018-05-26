#pragma once
#include "stdafx.h"
#include "Unit.h"
#include "InterfaceButton.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>

class Scene
{
protected:
	//sf::Window *window;
	sf::Font font;
	sf::Event event;
	sf::Mouse mouse;
	Knight knight;
public:
	int render();
	Scene();
	virtual ~Scene();
};

