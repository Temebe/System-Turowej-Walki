#pragma once
#include "Scene.h"
#include "Save.h"
#include <vector>

class BattlegroundScene :
	public Scene
{
	std::vector <unsigned int> teamA, teamB;
	bool mouseHold, nullSquare, holding;
	Square *first, *temp, *prev, *actual;
	sf::Texture mapTile, mapTileTouched;
	sf::Vector2i prevPos;
	int x, y;
	sf::Text text1, text2;
public:
	int render(sf::RenderWindow& window, Save& save, sf::View& view);
	BattlegroundScene();
	~BattlegroundScene();
};

