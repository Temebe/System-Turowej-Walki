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

bool Unit::isMouseOver(sf::Mouse & mouse, sf::RenderWindow & window)
{
	int x, y;
	x = this->getTexture()->getSize().x;
	y = this->getTexture()->getSize().y;
	if ((mouse.getPosition(window).x >= this->getPosition().x) && (mouse.getPosition(window).y >= this->getPosition().y)
		&& (mouse.getPosition(window).x <= this->getPosition().x + x) && (mouse.getPosition(window).y <= this->getPosition().y + y)) {
		return true;
	}
	else
		return false;
}

Knight::Knight()
{
	texture.loadFromFile("include/characters/knight.png");
	this->setTexture(texture);
}

Knight::~Knight()
{

}
