#include "stdafx.h"
#include "Unit.h"
#include <iostream>


Unit::Unit()
{
}

Unit::Unit(bool choice)
{
	team = choice;
}

void Unit::resetMovement()
{
	tempMovement = movement;
}

void Unit::lossTempMovement(int value)
{
	tempMovement = tempMovement - value;
}

int Unit::getTempMovement()
{
	return tempMovement;
}

void Unit::setType(int value)
{
	type = value;
}

int Unit::getType()
{
	return type;
}

void Unit::setHPBarTexture(sf::Texture& texture)
{
	hpBar->setTexture(texture);
}

void Unit::setHPBar(sf::Sprite * bar)
{
	hpBar = bar;
}

sf::Sprite *Unit::getHPBar()
{
	return hpBar;
}

bool Unit::isTeamA()
{
	return team;
}

bool Unit::hadTurn()
{
	return turn;
}

void Unit::setTurn(bool val)
{
	turn = val;
}


Unit::~Unit()
{
}

/*void Unit::move(Square *location, Square *destination)
{
	destination->putUnit(this);
	location->putUnit(nullptr);
	lossTempMovement(destination->getMovementCost());
}*/

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

}

Knight::Knight(bool choice)
{
	team = choice;
	movement = 2;
	tempMovement = 2;
	turn = false;
	std::cout << "Knight! " << tempMovement << std::endl;
}

Knight::~Knight()
{

}

Warrior::Warrior()
{

}

Warrior::Warrior(bool choice)
{
	team = choice;
	movement = 2;
	tempMovement = 2;
	turn = false;
}

Warrior::~Warrior()
{

}

Mage::Mage()
{

}

Mage::Mage(bool choice)
{
	team = choice;
	movement = 2;
	tempMovement = 2;
	turn = false;
}

Mage::~Mage()
{

}

Archer::Archer()
{

}

Archer::Archer(bool choice)
{
	team = choice;
	movement = 3;
	tempMovement = 3;
	turn = false;
}

Archer::~Archer()
{

}

Rider::Rider()
{

}

Rider::Rider(bool choice)
{
	team = choice;
	movement = 5;
	tempMovement = 5;
	turn = false;
}

Rider::~Rider()
{

}



