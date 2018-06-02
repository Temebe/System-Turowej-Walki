#pragma once
#include <SFML\Graphics.hpp>
#include "Square.h"
class Square;

class Unit
	:public sf::Sprite
{
private:
protected:
	bool team; // true -> A team, false -> B team;
	bool turn, hasAttacked, propTarget, movable;
	int maxHp, movement, tempMovement, attackRange; //hp -> health points
	double hp;
	sf::Sprite *hpBar;
	int type;
public:
	Unit();
	Unit(bool choice);
	void resetMovement();
	void lossTempMovement(int value);
	int getTempMovement();
	void setType(int value);
	int getType();
	void setHPBarTexture(sf::Texture& texture);
	void setHPBar(sf::Sprite *bar);
	int getAttackRange();
	sf::Sprite *getHPBar();
	bool isTeamA();
	bool hadTurn();
	bool canAttack();
	void setMovable(bool val);
	bool isMovable();
	void prepareForTurn();
	void setTurn(bool val);
	void takeDmg(double amount);
	void setPropTarget(bool val);
	bool isPropTarget();
	virtual ~Unit();
	virtual void attack(Square *target) = 0;
	//void move(Square *location, Square *destination);
	//virtual void findEnemy(Square *location, sf::Texture& mapTileAble, sf::Texture &mapTile, bool val) = 0;
	bool isMouseOver(sf::Mouse& mouse, sf::RenderWindow& window);
};

class Knight
	:public virtual Unit
{
public:
	Knight();
	Knight(bool choice);
	void attack(Square *target);
	~Knight();
	//void findEnemy(Square *location, sf::Texture& mapTileAble, sf::Texture &mapTile, bool val);
};

class Warrior
	:public Unit
{
public:
	Warrior(bool choice);
	void attack(Square *target);
	Warrior();
	~Warrior();
};

class Archer
	:public Unit
{
public:
	Archer(bool choice);
	void attack(Square *target);
	Archer();
	~Archer();
};

class Mage
	:public Unit
{
public:
	Mage(bool choice);
	void attack(Square *target);
	Mage();
	~Mage();
};

class Rider
	:public Unit
{
public:
	Rider(bool choice);
	void attack(Square *target);
	Rider();
	~Rider();
};

