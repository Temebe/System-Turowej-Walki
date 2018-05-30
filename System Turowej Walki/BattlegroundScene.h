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
	sf::Texture knightImA, warriorImA, mageImA, riderImA, archerImA;
	sf::Texture knightImB, warriorImB, mageImB, riderImB, archerImB;
	sf::Vector2i prevPos;
	int x, y;
	unsigned int KnA, WaA, ArA, RiA, MaA, KnB, WaB, ArB, RiB, MaB;
	sf::Text text1, text2;
	sf::Sprite selectedUnit;
	enum UnitType {KnightA, WarriorA, ArcherA, RiderA, MageA, KnightB, WarriorB, ArcherB, RiderB, MageB};
	UnitType unitType;

public:
	int render(sf::RenderWindow& window, Save& save, sf::View& view);
	void changeTeamSelect();
	void changeUnitSelect(UnitType& unit);
	void setUpUnit(Square *temp ,sf::Texture& texture);
	BattlegroundScene();
	~BattlegroundScene();
};

