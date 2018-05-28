#include "stdafx.h"
#include "SelectScene.h"
#include <cstdlib>


int SelectScene::render(sf::RenderWindow& window, Save& save)
{
	bool mouseHold;
	while (true) {
		window.clear(sf::Color::Black);
		window.draw(test);
		//Ikony klas
		window.draw(knightA);
		window.draw(knightB);
		window.draw(warriorA);
		window.draw(warriorB);
		window.draw(mageA);
		window.draw(mageB);
		window.draw(archerA);
		window.draw(archerB);
		window.draw(riderA);
		window.draw(riderB);
		//Przyciski + i -
		window.draw(upa1);
		window.draw(upa2);
		window.draw(upa3);
		window.draw(upa4);
		window.draw(upa5);
		window.draw(dna1);
		window.draw(dna2);
		window.draw(dna3);
		window.draw(dna4);
		window.draw(dna5);
		window.draw(upb1);
		window.draw(upb2);
		window.draw(upb3);
		window.draw(upb4);
		window.draw(upb5);
		window.draw(dnb1);
		window.draw(dnb2);
		window.draw(dnb3);
		window.draw(dnb4);
		window.draw(dnb5);
		//Texty ilosci jednostek
		window.draw(a1);
		window.draw(a2);
		window.draw(a3);
		window.draw(a4);
		window.draw(a5);
		window.draw(b1);
		window.draw(b2);
		window.draw(b3);
		window.draw(b4);
		window.draw(b5);
		window.draw(upMap);
		window.draw(dnMap);
		window.draw(mapSizeText);
		window.draw(startGame);
		window.pollEvent(event);
		/*if (event.type == sf::Event::Closed) {
			window.close();
			return 5;
		} JAK TO NAPRAWIC*/
		if ((event.type == sf::Event::MouseButtonPressed)&&(mouseHold != true)) {
			mouseHold = true;
			if(upa1.isMouseOver(mouse, window)) {
				std::cout << "upa1" << std::endl;
				va1++;
				sa1 = std::to_string(va1);
				a1.setString(sa1);
			}
			if (dna1.isMouseOver(mouse, window)) {
				std::cout << "dna1" << std::endl;
				va1--;
				sa1 = std::to_string(va1);
				a1.setString(sa1);
			}
			if (upa2.isMouseOver(mouse, window)) {
				std::cout << "upa2" << std::endl;
				va2++;
				sa2 = std::to_string(va2);
				a2.setString(sa2);
			}
			if (dna2.isMouseOver(mouse, window)) {
				std::cout << "dna2" << std::endl;
				va2--;
				sa2 = std::to_string(va2);
				a2.setString(sa2);
			}
			if (upa3.isMouseOver(mouse, window)) {
				std::cout << "upa3" << std::endl;
				va3++;
				sa3 = std::to_string(va3);
				a3.setString(sa3);
			}
			if (dna3.isMouseOver(mouse, window)) {
				std::cout << "dna3" << std::endl;
				va3--;
				sa3 = std::to_string(va3);
				a3.setString(sa3);
			}
			if (upa4.isMouseOver(mouse, window)) {
				std::cout << "upa4" << std::endl;
				va4++;
				sa4 = std::to_string(va4);
				a4.setString(sa4);
			}
			if (dna4.isMouseOver(mouse, window)) {
				std::cout << "dna4" << std::endl;
				va4--;
				sa4 = std::to_string(va4);
				a4.setString(sa4);
			}
			if (upa5.isMouseOver(mouse, window)) {
				std::cout << "upa5" << std::endl;
				va5++;
				sa5 = std::to_string(va5);
				a5.setString(sa5);
			}
			if (dna5.isMouseOver(mouse, window)) {
				std::cout << "dna5" << std::endl;
				va5--;
				sa5 = std::to_string(va5);
				a5.setString(sa5);
			}
			if (upb1.isMouseOver(mouse, window)) {
				std::cout << "upb1" << std::endl;
				vb1++;
				sb1 = std::to_string(vb1);
				b1.setString(sb1);
			}
			if (dnb1.isMouseOver(mouse, window)) {
				std::cout << "dnb1" << std::endl;
				vb1--;
				sb1 = std::to_string(vb1);
				b1.setString(sb1);
			}
			if (upb2.isMouseOver(mouse, window)) {
				std::cout << "upb2" << std::endl;
				vb2++;
				sb2 = std::to_string(vb2);
				b2.setString(sb2);
			}
			if (dnb2.isMouseOver(mouse, window)) {
				std::cout << "dnb2" << std::endl;
				vb2--;
				sb2 = std::to_string(vb2);
				b2.setString(sb2);
			}
			if (upb3.isMouseOver(mouse, window)) {
				std::cout << "upb3" << std::endl;
				vb3++;
				sb3 = std::to_string(vb3);
				b3.setString(sb3);
			}
			if (dnb3.isMouseOver(mouse, window)) {
				std::cout << "dnb3" << std::endl;
				vb3--;
				sb3 = std::to_string(vb3);
				b3.setString(sb3);
			}
			if (upb4.isMouseOver(mouse, window)) {
				std::cout << "upb4" << std::endl;
				vb4++;
				sb4 = std::to_string(vb4);
				b4.setString(sb4);
			}
			if (dnb4.isMouseOver(mouse, window)) {
				std::cout << "dnb4" << std::endl;
				vb4--;
				sb4 = std::to_string(vb4);
				b4.setString(sb4);
			}
			if (upb5.isMouseOver(mouse, window)) {
				std::cout << "upb5" << std::endl;
				vb5++;
				sb5 = std::to_string(vb5);
				b5.setString(sb5);
			}
			if (dnb5.isMouseOver(mouse, window)) {
				std::cout << "dnb5" << std::endl;
				vb5--;
				sb5 = std::to_string(vb5);
				b5.setString(sb5);
			}
			if (upMap.isMouseOver(mouse, window)) {
				std::cout << "upMap" << std::endl;
				mapSize++;
				mapSizeText.setString(std::to_string(mapSize) + "x" + std::to_string(mapSize));
			}
			if (dnMap.isMouseOver(mouse, window)) {
				std::cout << "dnMap" << std::endl;
				if (mapSize != 0) {
					mapSize--;
					mapSizeText.setString(std::to_string(mapSize) + "x" + std::to_string(mapSize));
				}
			}
			if (startGame.isMouseOver(mouse, window)) {
				std::cout << "start game" << std::endl;
				//1 -> knight, 2 -> warrior, 3 -> archer, 4 -> rider, 5 -> mage
				save.setTeamA(va1, va3, va2, va5, va4);
				save.setTeamB(vb1, vb3, vb2, vb5, vb4);
				save.setMapSize(mapSize);
				return 4;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
		}
		window.display();
	}
}

SelectScene::SelectScene()
{
	va1 = va2 = va3 = va4 = va5 = vb1 = vb2 = vb3 = vb4 = vb5 = 0;
	sa1 = std::to_string(va1);
	sa2 = std::to_string(va2);
	sa3 = std::to_string(va3);
	sa4 = std::to_string(va4);
	sa5 = std::to_string(va5);
	sb1 = std::to_string(vb1);
	sb2 = std::to_string(vb2);
	sb3 = std::to_string(vb3);
	sb4 = std::to_string(vb4);
	sb5 = std::to_string(vb5);
	sa2 = sa3 = sa4 = sa5 = sb1 = sb2 = sb3 = sb4 = sb5 = sa1;
	a1.setFillColor(sf::Color::White);
	a1.setFont(font);
	a2.setFont(font);
	a3.setFont(font);
	a4.setFont(font);
	a5.setFont(font);
	b1.setFont(font);
	b2.setFont(font);
	b3.setFont(font);
	b4.setFont(font);
	b5.setFont(font);
	test.setFont(font);
	test.setString("WYBIERZ JEDNOSTKI");
	test.setFillColor(sf::Color::Red);
	test.setPosition(200, 200);
	up.loadFromFile("include/buttons/+.png");
	dn.loadFromFile("include/buttons/-.png");
	knightIm.loadFromFile("include/characters/knight.png");
	warriorIm.loadFromFile("include/characters/warrior.png");
	archerIm.loadFromFile("include/characters/archer.png");
	riderIm.loadFromFile("include/characters/rider.png");
	mageIm.loadFromFile("include/characters/mage.png");
	knightA.setTexture(knightIm);
	knightB.setTexture(knightIm);
	warriorA.setTexture(warriorIm);
	warriorB.setTexture(warriorIm);
	archerA.setTexture(archerIm);
	archerB.setTexture(archerIm);
	riderA.setTexture(riderIm);
	riderB.setTexture(riderIm);
	mageA.setTexture(mageIm);
	mageB.setTexture(mageIm);
	knightA.setPosition(20, 50);
	knightB.setPosition(876, 50);
	warriorA.setPosition(20, 198);
	warriorB.setPosition(876, 198);
	archerA.setPosition(20, 346);
	archerB.setPosition(876, 346);
	riderA.setPosition(20, 494);
	riderB.setPosition(876, 494);
	mageA.setPosition(20, 642);
	mageB.setPosition(876, 642);
	//knightA.setScale(0.5, 0.5);
	upa1.setTexture(up);
	upa2.setTexture(up);
	upa3.setTexture(up);
	upa4.setTexture(up);
	upa5.setTexture(up);
	upb1.setTexture(up);
	upb2.setTexture(up);
	upb3.setTexture(up);
	upb4.setTexture(up);
	upb5.setTexture(up);
	dna1.setTexture(dn);
	dna2.setTexture(dn);
	dna3.setTexture(dn);
	dna4.setTexture(dn);
	dna5.setTexture(dn);
	dnb1.setTexture(dn);
	dnb2.setTexture(dn);
	dnb3.setTexture(dn);
	dnb4.setTexture(dn);
	dnb5.setTexture(dn);
	upa1.setPosition(148, 50);
	dna1.setPosition(148, 148);
	upa2.setPosition(148, 198);
	dna2.setPosition(148, 296);
	upa3.setPosition(148, 346);
	dna3.setPosition(148, 444);
	upa4.setPosition(148, 494);
	dna4.setPosition(148, 592);
	upa5.setPosition(148, 642);
	dna5.setPosition(148, 740);
	upb1.setPosition(846, 50);
	dnb1.setPosition(846, 148);
	upb2.setPosition(846, 198);
	dnb2.setPosition(846, 296);
	upb3.setPosition(846, 346);
	dnb3.setPosition(846, 444);
	upb4.setPosition(846, 494);
	dnb4.setPosition(846, 592);
	upb5.setPosition(846, 642);
	dnb5.setPosition(846, 740);
	a1.setString(sa1);
	a2.setString(sa2);
	a3.setString(sa3);
	a4.setString(sa4);
	a5.setString(sa5);
	b1.setString(sb1);
	b2.setString(sb2);
	b3.setString(sb3);
	b4.setString(sb4);
	b5.setString(sb5);
	a1.setPosition(148, 100);
	a2.setPosition(148, 248);
	a3.setPosition(148, 396);
	a4.setPosition(148, 544);
	a5.setPosition(148, 692);
	b1.setPosition(846, 100);
	b2.setPosition(846, 248);
	b3.setPosition(846, 396);
	b4.setPosition(846, 544);
	b5.setPosition(846, 692);
	upMap.setTexture(up);
	dnMap.setTexture(dn);
	upMap.setPosition(462, 300);
	dnMap.setPosition(542, 300);
	mapSizeText.setFont(font);
	mapSizeText.setPosition(500, 250);
	mapSizeText.setString("0x0");
	mapSize = 0;
	startGameTxt.loadFromFile("include/buttons/startgame.png");
	startGame.setTexture(startGameTxt);
	startGame.setPosition(437, 700);
}

SelectScene::~SelectScene()
{
}
