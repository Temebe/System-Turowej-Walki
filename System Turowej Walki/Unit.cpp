#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}

Unit::Unit(bool choice)
{
	team = choice;
}

bool Unit::isTeamA()
{
	return team;
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

}

Knight::Knight(bool choice)
{
	team = choice;
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
}

Rider::~Rider()
{

}



