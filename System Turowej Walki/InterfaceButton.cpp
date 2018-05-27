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

bool InterfaceButton::isMouseOver(sf::Mouse& mouse)
{

	return false;
}
