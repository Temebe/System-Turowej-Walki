#include "stdafx.h"
#include "Unit.h"


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


Unit::~Unit()
{
}

void Unit::move(Square * location, Square * destination)
{
	location->putUnit(nullptr);
	destination->putUnit(this);
	this->tempMovement = this->tempMovement - destination->getMovementCost();
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

}

Knight::Knight(bool choice)
{
	team = choice;
	movement = 2;
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
}

Rider::~Rider()
{

}



