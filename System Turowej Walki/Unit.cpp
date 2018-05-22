#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

void Unit::move()
{
}

Knight::Knight()
{
	texture.loadFromFile("include/characters/knight.png");
	this->setTexture(texture);
}

Knight::~Knight()
{

}
