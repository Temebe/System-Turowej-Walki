#pragma once
#include "Scene.h"
class MenuScene :
	public Scene
{
	InterfaceButton newGame, loadGame, options, exit;
	sf::Text test, version;
public:
	MenuScene();
	~MenuScene();
	int render(sf::RenderWindow& window);
};

