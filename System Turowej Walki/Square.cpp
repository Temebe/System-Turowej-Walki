#include "stdafx.h"
#include "Square.h"

void Square::setLeft(Square * temp)
{
	if (temp == nullptr) left = nullptr;
	else left = temp;
}

void Square::setRight(Square * temp)
{
	if (temp == nullptr) left = nullptr;
	else right = temp;
}

void Square::setUp(Square * temp)
{
	if (temp == nullptr) left = nullptr;
	else up = temp;
}

void Square::setDown(Square * temp)
{
	if (temp == nullptr) left = nullptr;
	else down = temp;
}

void Square::setAble(bool & temp)
{
	ableToMove = temp;
}

void Square::setMovementCost(int & value)
{
	movementCost = value;
}

int Square::getMovementCost()
{
	return movementCost;
}

bool Square::isAbleToMove()
{
	return ableToMove;
}

bool Square::isTouched()
{
	return touched;
}

void Square::touch()
{
	touched = !touched;
}

void Square::putUnit(Unit * unit)
{
	occupyingUnit = unit;
}

Unit *Square::getUnit()
{
	return occupyingUnit;
}

Square *Square::getLeft()
{
	if (left == nullptr) return nullptr;
	else return left;
}

Square *Square::getRight()
{
	if (right == nullptr) return nullptr;
	return right;
}

Square *Square::getUp()
{
	if (up == nullptr) return nullptr;
	return up;
}

Square *Square::getDown()
{
	if (down == nullptr) return nullptr;
	return down;
}

Square::Square()
{
	left = nullptr;
	right = nullptr;
	up = nullptr;
	down = nullptr;
	occupyingUnit = nullptr;
	touched = false;
	movementCost = 0;
}


Square::~Square()
{
}


