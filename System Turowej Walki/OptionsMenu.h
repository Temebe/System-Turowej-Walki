#pragma once
#include "Scene.h"
class OptionsMenu :
	public Scene
{
	bool mouseHold;
	InterfaceButton volUp, volDn, returnButton;
	sf::Texture up, dn;
	sf::Text volText;
public:
	OptionsMenu();
	~OptionsMenu();
	int render(sf::RenderWindow& window, sf::Music& music);
};

