#pragma once
#include "Scene.h"
class SelectScene :
	public Scene
{
	sf::Text test;
public:
	int render();
	SelectScene();
	~SelectScene();
};

