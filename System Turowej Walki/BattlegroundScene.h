#pragma once
#include "Scene.h"
#include "Save.h"
#include <vector>

class BattlegroundScene :
	public Scene
{
	std::vector <unsigned int> teamA, teamB;
	std::vector <Unit*> knightsA, knightsB;
	std::vector <Unit*> warriorsA, warriorsB;
	std::vector <Unit*> archersA, archersB;
	std::vector <Unit*> magesA, magesB;
	std::vector <Unit*> ridersA, ridersB;
	bool mouseHold, nullSquare, holding, unitUIClicked;
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
	enum TurnType {nothing, chooseDirection, chooseTarget, won};
	TurnType turnType;
	InterfaceButton fight, move, idle;
	sf::Texture fightIm, moveIm, idleIm;

public:
	int render(sf::RenderWindow& window, Save& save, sf::View& view);
	void changeTeamSelect();
	void changeUnitSelect(UnitType& unit);
	//void changeUnitTurn(UnitType& unit);
	void setUpUnit(Square *temp ,sf::Texture& texture);
	bool isHisTurn(Square *temp);
	void changeUnitTurn(UnitType& type);
	Square * findWay(Square * temp, int movement, int iteration, bool val);
	Square * findEnemy(Square *temp, int attackRange, bool val, bool firstIteration);
	void nothingTurn(sf::RenderWindow & window, sf::View & view);
	void chooseDirectionTurn(sf::RenderWindow & window, sf::View & view);
	void chooseTargetTurn(sf::RenderWindow & window, sf::View & view);
	void setNewTurn();
	void unitUICheck(sf::RenderWindow & window, sf::View & view);
	void unitUICheck(sf::Event& event);
	void checkIfUnitFinished(Unit *tempUnit);
	bool checkIfWon();
	void moveUnit(Square *location, Square *destination, Unit& unit);
	BattlegroundScene();
	~BattlegroundScene();
};

