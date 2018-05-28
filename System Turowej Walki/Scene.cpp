#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	if (!font.loadFromFile("include/Calibri.ttf"))
	{
		std::cout << "Unable to load font" << std::endl;
	}
}


Scene::~Scene()
{
}
