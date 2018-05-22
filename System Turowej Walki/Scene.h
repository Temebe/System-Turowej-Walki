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
	sf::Font font;
	sf::Event event;
	sf::RenderWindow window;
	sf::Mouse mouse;
	Knight knight;
public:
	int render();
	Scene();
	virtual ~Scene();
};

