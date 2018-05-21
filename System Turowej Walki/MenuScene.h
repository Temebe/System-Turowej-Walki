#pragma once
#include "Scene.h"
class MenuScene :
	public Scene
{
	InterfaceButton newGame, loadGame, options, exit;
	sf::Text test;
public:
	MenuScene();
	virtual ~MenuScene();
	void render();
};

