#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	if (!font.loadFromFile("include/Calibri.ttf"))
	{
		std::cout << "Font nam sie zesral" << std::endl;
	}
	window.setFramerateLimit(60);
}


Scene::~Scene()
{
}
