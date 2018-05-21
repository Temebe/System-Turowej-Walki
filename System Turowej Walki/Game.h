#pragma once
#include "stdafx.h"
#include "Unit.h"
#include "InterfaceButton.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include "MenuScene.h"

class Game
{
	MenuScene menuScene;
public:
	Game();
	virtual ~Game();
	void run();
};

