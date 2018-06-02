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

int Unit::getAttackRange()
{
	return attackRange;
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

bool Unit::canAttack()
{
	return !hasAttacked;
}

void Unit::setTurn(bool val)
{
	turn = val;
}

void Unit::takeDmg(int amount)
{
	hp = hp - amount;
	std::cout << "Hit! Hp left: " << hp << std::endl;
	if (hp <= 0) {
		std::cout << "Died" << std::endl;
		this->getHPBar()->setScale((float)0, 1);
	}
	else {
		this->getHPBar()->setScale((float)hp / maxHp, 1);
	}
}

void Unit::setPropTarget(bool val)
{
	propTarget = val;
}

bool Unit::isPropTarget()
{
	return propTarget;
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
	maxHp = 15;
	hp = 15;
	movement = 2;
	tempMovement = 2;
	attackRange = 1;
	turn = false;
	std::cout << "Knight! " << tempMovement << std::endl;
}

void Knight::attack(Unit * target)
{
	target->takeDmg(2);
	this->hasAttacked = true;
}

Knight::~Knight()
{

}

/*void Knight::findEnemy(Square * location, sf::Texture & mapTileAble, sf::Texture & mapTile, bool val)
{

}*/

Warrior::Warrior()
{

}

Warrior::Warrior(bool choice)
{
	team = choice;
	maxHp = 10;
	hp = 10;
	movement = 2;
	tempMovement = 2;
	attackRange = 1;
	turn = false;
}

void Warrior::attack(Unit * target)
{

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
	maxHp = 8;
	hp = 8;
	movement = 2;
	tempMovement = 2;
	attackRange = 2;
	turn = false;
}

void Mage::attack(Unit * target)
{

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
	maxHp = 8;
	hp = 8;
	movement = 3;
	tempMovement = 3;
	attackRange = 3;
	turn = false;
}

void Archer::attack(Unit * target)
{

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
	maxHp = 12;
	hp = 12;
	movement = 5;
	tempMovement = 5;
	attackRange = 1;
	turn = false;
}

void Rider::attack(Unit * target)
{

}

Rider::~Rider()
{

}



