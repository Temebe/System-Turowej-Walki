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
	if (tempMovement <= 0) movable = false;
}

int Unit::getTempMovement()
{
	return tempMovement;
}

void Unit::setType(int value)
{
	type = value;
}

void Unit::setTempMovement(int value)
{
	tempMovement = value;
}

void Unit::setHp(double value)
{
	hp = value;
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

void Unit::setAttackAbility(bool val)
{
	hasAttacked = !val;
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

double Unit::getHp()
{
	return hp;
}

void Unit::setMovable(bool val)
{
	movable = val;
}

bool Unit::isMovable()
{
	return movable;
}

void Unit::prepareForTurn()
{
	hasAttacked = false;
	turn = false;
	tempMovement = movement;
	movable = true;
}

void Unit::setTurn(bool val)
{
	turn = val;
}

void Unit::takeDmg(double amount)
{
	hp = hp - amount;
	std::cout << "Hit! Hp left: " << hp << std::endl;
	if (hp <= 0) {
		std::cout << "Died" << std::endl;
		delete this;
	}
	else {
		this->getHPBar()->setScale((float)hp / maxHp, 0.4);
	}
}

void Unit::setPropTarget(bool val)
{
	propTarget = val;
}

void Unit::setParentSquare(Square * parent)
{
	parentSquare = parent;
}

bool Unit::isPropTarget()
{
	return propTarget;
}


Unit::~Unit()
{
	std::cout << "KUKU" << std::endl;
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

Knight::Knight(bool choice, std::vector<Unit*> *parent)
{
	team = choice;
	maxHp = 15;
	hp = 15;
	movement = 2;
	tempMovement = 2;
	attackRange = 1;
	turn = false;
	movable = true;
	std::cout << "Knight! " << tempMovement << std::endl;
	parentVector = parent;
}

void Knight::attack(Square *target)
{
	target->getUnit()->takeDmg(2);
	this->hasAttacked = true;
}

Knight::~Knight()
{
	parentVector->erase(std::remove(parentVector->begin(), parentVector->end(), this), parentVector->end());
	delete hpBar;
	parentSquare->putUnit(nullptr);
}

/*void Knight::findEnemy(Square * location, sf::Texture & mapTileAble, sf::Texture & mapTile, bool val)
{

}*/

Warrior::Warrior()
{

}

Warrior::Warrior(bool choice, std::vector<Unit*> *parent)
{
	team = choice;
	maxHp = 10;
	hp = 10;
	movement = 2;
	tempMovement = 2;
	attackRange = 1;
	turn = false;
	movable = true;
	parentVector = parent;
}

void Warrior::attack(Square *target)
{
	target->getUnit()->takeDmg(3);
	this->hasAttacked = true;
}

Warrior::~Warrior()
{
	parentVector->erase(std::remove(parentVector->begin(), parentVector->end(), this), parentVector->end());
	delete hpBar;
	parentSquare->putUnit(nullptr);
}

Mage::Mage()
{

}

Mage::Mage(bool choice, std::vector<Unit*> *parent)
{
	team = choice;
	maxHp = 8;
	hp = 8;
	movement = 2;
	tempMovement = 2;
	attackRange = 2;
	turn = false;
	movable = true;
	parentVector = parent;
}

void Mage::attack(Square *target)
{
	target->getUnit()->takeDmg(3);
	if (target->getRight() != nullptr) {
		if (target->getRight()->getUnit() != nullptr)
			target->getRight()->getUnit()->takeDmg(2);
	}
	if (target->getLeft() != nullptr) {
		if (target->getLeft()->getUnit() != nullptr)
			target->getLeft()->getUnit()->takeDmg(2);
	}
	if (target->getUp() != nullptr) {
		if (target->getUp()->getUnit() != nullptr)
			target->getUp()->getUnit()->takeDmg(2);
	}
	if (target->getDown() != nullptr) {
		if (target->getDown()->getUnit() != nullptr)
			target->getDown()->getUnit()->takeDmg(2);
	}
	this->hasAttacked = true;
}

Mage::~Mage()
{
	parentVector->erase(std::remove(parentVector->begin(), parentVector->end(), this), parentVector->end());
	delete hpBar;
	parentSquare->putUnit(nullptr);
}

Archer::Archer()
{

}

Archer::Archer(bool choice, std::vector<Unit*> *parent)
{
	team = choice;
	maxHp = 8;
	hp = 8;
	movement = 3;
	tempMovement = 3;
	attackRange = 3;
	turn = false;
	movable = true;
	parentVector = parent;
}

void Archer::attack(Square *target)
{
	target->getUnit()->takeDmg(1.5);
	this->hasAttacked = true;
}

Archer::~Archer()
{
	parentVector->erase(std::remove(parentVector->begin(), parentVector->end(), this), parentVector->end());
	delete hpBar;
	parentSquare->putUnit(nullptr);
}

Rider::Rider()
{

}

Rider::Rider(bool choice, std::vector<Unit*> *parent)
{
	team = choice;
	maxHp = 12;
	hp = 12;
	movement = 5;
	tempMovement = 5;
	attackRange = 1;
	turn = false;
	movable = true;
	parentVector = parent;
}

void Rider::attack(Square *target)
{
	target->getUnit()->takeDmg((movement - tempMovement)*1.5);
	this->hasAttacked = true;
}

Rider::~Rider()
{
	parentVector->erase(std::remove(parentVector->begin(), parentVector->end(), this), parentVector->end());
	delete hpBar;
	parentSquare->putUnit(nullptr);
}



