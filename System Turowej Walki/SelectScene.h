#pragma once
#include "Scene.h"

class SelectScene :
	public Scene
{
	sf::Text test;
	InterfaceButton upa1, upa2, upa3, upa4, upa5, upb1, upb2, upb3, upb4, upb5;
	InterfaceButton dna1, dna2, dna3, dna4, dna5, dnb1, dnb2, dnb3, dnb4, dnb5;
public:
	int render();
	SelectScene();
	~SelectScene();
};

