#pragma once
#include "Scene.h"
#include "Save.h"
#include <vector>

class BattlegroundScene :
	public Scene
{
	std::vector <unsigned int> teamA, teamB;
	bool mouseHold, nullSquare, holding;
	bool selectingMode, teamASelecting, unitUI;
	Square *first, *temp, *prev, *actual;
	sf::IntRect intRect;
	sf::Texture mapTile, mapTileTouched, mapTileAble, hpbarIm;
	sf::Texture knightImA, warriorImA, mageImA, riderImA, archerImA;
	sf::Texture knightImB, warriorImB, mageImB, riderImB, archerImB;
	sf::Vector2i clickedPos;
	int x, y;
	unsigned int KnA, WaA, ArA, RiA, MaA, KnB, WaB, ArB, RiB, MaB;
	sf::Text text1, text2;
	sf::Sprite selectedUnit;
	enum UnitType {KnightA, WarriorA, ArcherA, RiderA, MageA, KnightB, WarriorB, ArcherB, RiderB, MageB};
	UnitType unitType;
	InterfaceButton fight, move, idle;
	sf::Texture fightIm, moveIm, idleIm;

public:
	int render(sf::RenderWindow& window, Save& save, sf::View& view);
	void changeTeamSelect();
	void changeUnitSelect(UnitType& unit);
	void setUpUnit(Square *temp ,sf::Texture& texture);
	bool isInRightTeam(Square *temp);
	Square * findWay(Square * temp, int movement, int iteration, bool val);
	BattlegroundScene();
	~BattlegroundScene();
};

