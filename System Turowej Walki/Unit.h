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
	bool isMouseOver(sf::Mouse& mouse, sf::RenderWindow& window);
};

class Knight
	:public Unit
{
	sf::Texture texture;
public:
	Knight();
	~Knight();
};

