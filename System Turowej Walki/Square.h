#pragma once
#include <SFML/Graphics.hpp>
#include "Unit.h"

class Square
	:public sf::Sprite
{
	sf::Vector2u pos;
	Unit *occupyingUnit;
	bool touched, ableToMove;
	Square *left, *right, *up, *down;
	int movementCost;
public:
	void setLeft(Square *temp);
	void setRight(Square *temp);
	void setUp(Square *temp);
	void setDown(Square *temp);
	void setAble(bool& temp);
	void setMovementCost(int& value);
	int getMovementCost();
	bool isAbleToMove();
	bool isTouched();
	void touch();
	void putUnit(Unit *unit);
	Unit *getUnit();
	Square *getLeft();
	Square *getRight();
	Square *getUp();
	Square *getDown();
	Square();
	~Square();
};

