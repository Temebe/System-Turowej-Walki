#pragma once
#include "Square.h"
#include <vector>

class Save
{
	Square *first; //pointer to left corner of the map
	unsigned int knightsA, knightsB, archersA, archersB, warriorsA, warriorsB;
	unsigned int magesA, magesB, ridersA, ridersB, mapSize;
	std::vector <unsigned int> teamA, teamB; //0-> knight, 1-> warrior, 2-> archer, 3-> rider, 4-> mage
public:
	void saveToFile();
	void loadFromFile();
	void setTeamA(unsigned int& knights, unsigned int& archers, unsigned int& warriors, unsigned int& mages, unsigned int& riders);
	void setTeamB(unsigned int& knights, unsigned int& archers, unsigned int& warriors, unsigned int& mages, unsigned int& riders);
	std::vector <unsigned int> getTeamA();
	std::vector <unsigned int> getTeamB();
	unsigned int getMapSize();
	void setMapSize(unsigned int& value);
	Square *getFirst();
	void setFirst(Square *tmp);
	Save();
	~Save();
};

