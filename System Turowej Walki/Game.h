#pragma once
#include "stdafx.h"
#include "Unit.h"
#include "InterfaceButton.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>

class Game
{
public:
	Game();
	virtual ~Game();
	void run();
};

