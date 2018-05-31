#pragma once
#include <SFML\Graphics.hpp>
#include "Square.h"

class Unit
	:public sf::Sprite
{
private:
protected:
	bool team; // true -> A team, false -> B team;
	int hp, movement, tempMovement; //hp -> health points
	sf::Sprite *hpBar;
public:
	Unit();
	Unit(bool choice);
	void resetMovement();
	void lossTempMovement(int value);
	int getTempMovement();
	void setHPBarTexture(sf::Texture& texture);
	void setHPBar(sf::Sprite *bar);
	sf::Sprite *getHPBar();
	bool isTeamA();
	virtual ~Unit();
	void move(Square *location, Square *destination);
	bool isMouseOver(sf::Mouse& mouse, sf::RenderWindow& window);
};

class Knight
	:public Unit
{
public:
	Knight();
	Knight(bool choice);
	~Knight();
};

class Warrior
	:public Unit
{
public:
	Warrior(bool choice);
	Warrior();
	~Warrior();
};

class Archer
	:public Unit
{
public:
	Archer(bool choice);
	Archer();
	~Archer();
};

class Mage
	:public Unit
{
public:
	Mage(bool choice);
	Mage();
	~Mage();
};

class Rider
	:public Unit
{
public:
	Rider(bool choice);
	Rider();
	~Rider();
};

