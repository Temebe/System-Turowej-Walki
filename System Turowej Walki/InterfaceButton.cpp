#include "stdafx.h"
#include "InterfaceButton.h"
#include <string>
#include <iostream>


InterfaceButton::InterfaceButton()
{
}


InterfaceButton::~InterfaceButton()
{
}

void InterfaceButton::setTextureImage(std::string path)
{
	texture.loadFromFile(path);
	this->setTexture(texture);
}

bool InterfaceButton::isMouseOver(sf::Mouse& mouse, sf::RenderWindow& window)
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

bool InterfaceButton::isMouseOver(sf::Mouse& mouse, sf::RenderWindow& window, sf::View& view)
{
	int x, y, xView, yView;
	x = this->getTexture()->getSize().x;
	y = this->getTexture()->getSize().y;
	xView = view.getCenter().x - 512;
	yView = view.getCenter().y - 400;
	if ((mouse.getPosition(window).x >= this->getPosition().x - xView) && (mouse.getPosition(window).y >= this->getPosition().y - yView)
	&& (mouse.getPosition(window).x <= this->getPosition().x + x - xView) && (mouse.getPosition(window).y <= this->getPosition().y + y - yView)) {
		return true;
	}
	else
		return false;
}

//+ view.getCenter().x - 512)