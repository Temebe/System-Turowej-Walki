#pragma once
#include "Scene.h"
class BattlegroundScene :
	public Scene
{
	bool mouseHold;
public:
	int render(sf::RenderWindow& window);
	BattlegroundScene();
	~BattlegroundScene();
};

