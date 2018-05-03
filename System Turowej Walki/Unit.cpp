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
	texture.loadFromFile("include/characters/knight2.png");
	this->setTexture(texture);
}

Knight::~Knight()
{

}
