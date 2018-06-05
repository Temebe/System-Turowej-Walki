#pragma once
#include <SFML\Graphics.hpp>
#include "Square.h"
#include <vector>
class Square;

class Unit
	:public sf::Sprite
{
private:
protected:
	std::vector<Unit*> *parentVector;
	Square *parentSquare;
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
	void setTempMovement(int value);
	void setHp(double value);
	int getType();
	void setHPBarTexture(sf::Texture& texture);
	void setHPBar(sf::Sprite *bar);
	void setAttackAbility(bool val);
	int getAttackRange();
	sf::Sprite *getHPBar();
	bool isTeamA();
	bool hadTurn();
	bool canAttack();
	double getHp();
	int getMovement();
	int getMaxHp();
	void setMovable(bool val);
	bool isMovable();
	void prepareForTurn();
	void setTurn(bool val);
	void takeDmg(double amount);
	void setPropTarget(bool val);
	void setParentSquare(Square *parent);
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
	Knight(bool choice, std::vector<Unit*> *parent);
	void attack(Square *target);
	~Knight();
	//void findEnemy(Square *location, sf::Texture& mapTileAble, sf::Texture &mapTile, bool val);
};

class Warrior
	:public Unit
{
public:
	Warrior(bool choice, std::vector<Unit*> *parent);
	void attack(Square *target);
	Warrior();
	~Warrior();
};

class Archer
	:public Unit
{
public:
	Archer(bool choice, std::vector<Unit*> *parent);
	void attack(Square *target);
	Archer();
	~Archer();
};

class Mage
	:public Unit
{
public:
	Mage(bool choice, std::vector<Unit*> *parent);
	void attack(Square *target);
	Mage();
	~Mage();
};

class Rider
	:public Unit
{
public:
	Rider(bool choice, std::vector<Unit*> *parent);
	void attack(Square *target);
	Rider();
	~Rider();
};

