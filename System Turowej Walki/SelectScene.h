#pragma once
#include "Scene.h"
#include <string>
#include "Save.h"

class SelectScene :
	public Scene
{
	bool errorOccured, tutorialShown;
	enum ErrorCode {tooSmallMap, emptyTeams, notEqualTeams, tooManyUnits};
	unsigned int va1, va2, va3, va4, va5, vb1, vb2, vb3, vb4, vb5, mapSize;
	std::string sa1, sa2, sa3, sa4, sa5, sb1, sb2, sb3, sb4, sb5;
	sf::Text a1, a2, a3, a4, a5, b1, b2, b3, b4, b5, test, mapSizeText, errorText, description; //1 -> knight, 2 -> warrior, 3 -> archer, 4 -> rider, 5 -> mage
	sf::RectangleShape desprictionBg;
	sf::Texture up, dn, startGameTxt, errorBoxIm, tutorialIm;
	InterfaceButton upa1, upa2, upa3, upa4, upa5, upb1, upb2, upb3, upb4, upb5, upMap;
	InterfaceButton dna1, dna2, dna3, dna4, dna5, dnb1, dnb2, dnb3, dnb4, dnb5, dnMap, startGame, tutorial;
	sf::Texture knightImA, warriorImA, mageImA, riderImA, archerImA;
	sf::Texture knightImB, warriorImB, mageImB, riderImB, archerImB;
	sf::Texture GameTutorialIm;
	sf::Sprite GameTutorial;
	InterfaceButton knightA, knightB, warriorA, warriorB, mageA, mageB, archerA, archerB, riderA, riderB;
	InterfaceButton infoBg, errorBox;
	std::string knDes, waDes, arDes, maDes, riDes;
public:
	int render(sf::RenderWindow& window, Save& save);
	void mouseClicked(sf::RenderWindow& window);
	bool gameReady();
	void drawScene(sf::RenderWindow& window);
	void unitsDescriptions(sf::RenderWindow& window);
	SelectScene();
	~SelectScene();
};

