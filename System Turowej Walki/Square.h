#pragma once
#include <SFML/Graphics.hpp>
#include "Unit.h"

class Square
	:public sf::Sprite
{
	sf::Vector2u pos;
	Unit *occupyingUnit;
	bool touched;
	Square *left, *right, *up, *down;
public:
	void setLeft(Square *temp);
	void setRight(Square *temp);
	void setUp(Square *temp);
	void setDown(Square *temp);
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

