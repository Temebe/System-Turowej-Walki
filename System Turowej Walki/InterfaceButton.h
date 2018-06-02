#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class InterfaceButton
	:public sf::Sprite
{
	sf::Texture texture;
public:
	InterfaceButton();
	virtual ~InterfaceButton();
	void setTextureImage(std::string path);
	bool isMouseOver(sf::Mouse& mouse, sf::RenderWindow& window);
	bool isMouseOver(sf::Mouse& mouse, sf::RenderWindow& window, sf::View& view);
};

