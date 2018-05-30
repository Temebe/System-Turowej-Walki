#pragma once
#include <SFML\Graphics.hpp>

class Unit
	:public sf::Sprite
{
private:
protected:
	bool team; // true -> A team, false -> B team;
	int hp; //health points
public:
	Unit();
	Unit(bool choice);
	bool isTeamA();
	virtual ~Unit();
	void move();
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

