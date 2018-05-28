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
#include "SelectScene.h"
#include "OptionsMenu.h"
#include "BattlegroundScene.h"
#include "Save.h"

class Game
{
	sf::RenderWindow window;
	MenuScene menuScene;
	SelectScene selectScene;
	OptionsMenu optionsScene;
	BattlegroundScene battlegroundScene;
	Save save;
	sf::Music music;
	bool loaded;
	int actualScene; //0 -> menu, 1 -> options, 2 -> load game, 3 -> team select, 4 -> battleground, 5 -> exit
public:
	Game();
	virtual ~Game();
	void run();
	void setScene(int value);
};

