#include "stdafx.h"
#include "InterfaceButton.h"
#include <string>


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
