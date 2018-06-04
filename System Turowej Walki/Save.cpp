#include "stdafx.h"
#include "Save.h"


void Save::saveToFile(std::string & test)
{

}

void Save::setLoadingMode(bool val)
{
	loadingMode = val;
	selectingMode = !val;
}

void Save::setTeamA(unsigned int & knights, unsigned int & archers, unsigned int & warriors, unsigned int & mages, unsigned int & riders)
{
	teamA.push_back(knights);
	teamA.push_back(warriors);
	teamA.push_back(archers);
	teamA.push_back(riders);
	teamA.push_back(mages);
}

void Save::setTeamB(unsigned int & knights, unsigned int & archers, unsigned int & warriors, unsigned int & mages, unsigned int & riders)
{
	teamB.push_back(knights);
	teamB.push_back(warriors);
	teamB.push_back(archers);
	teamB.push_back(riders);
	teamB.push_back(mages);
}

std::vector<unsigned int> Save::getTeamA()
{
	return teamA;
}

std::vector<unsigned int> Save::getTeamB()
{
	return teamB;
}

unsigned int Save::getMapSize()
{
	return mapSize;
}

void Save::setMapSize(unsigned int & value)
{
	mapSize = value;
}

bool Save::isSelectingMode()
{
	return selectingMode;
}

bool Save::isLoadingMode()
{
	return loadingMode;
}

Square * Save::getFirst()
{
	return first;
}

void Save::setFirst(Square *tmp)
{
	first = tmp;
}

Save::Save()
{
}


Save::~Save()
{
}
