#pragma once
#include "Scene.h"
#include "Save.h"
#include <vector>

class BattlegroundScene :
	public Scene
{
	std::vector <unsigned int> teamA, teamB;
	bool mouseHold, nullSquare;
	Square *first, *temp, *prev, *actual;
	sf::Texture mapTile, mapTileTouched;
public:
	int render(sf::RenderWindow& window, Save& save, bool& loaded);
	BattlegroundScene();
	~BattlegroundScene();
};

