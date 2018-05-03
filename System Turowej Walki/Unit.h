#pragma once
#include <SFML\Graphics.hpp>

class Unit
	:public sf::Sprite
{
private:
	int hp; //health points
public:
	Unit();
	virtual ~Unit();
	void move();
};

class Knight
	:public Unit
{
	sf::Texture texture;
public:
	Knight();
	virtual ~Knight();
};

