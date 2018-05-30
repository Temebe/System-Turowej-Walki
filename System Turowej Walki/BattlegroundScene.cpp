#include "stdafx.h"
#include "BattlegroundScene.h"


int BattlegroundScene::render(sf::RenderWindow & window, Save& save, sf::View& view)
{
	mouseHold = false;
	//test
	//teamA = save.getTeamA();
	//teamB = save.getTeamB();
	/*std::cout << "Knights from team A: " << save.getTeamA().at(0) << std::endl;
	std::cout << "Warriors from team A: " << save.getTeamA().at(1) << std::endl;
	std::cout << "Archers from team A: " << save.getTeamA().at(2) << std::endl;
	std::cout << "Riders from team A: " << save.getTeamA().at(3) << std::endl;
	std::cout << "Mages from team A: " << save.getTeamA().at(4) << std::endl;
	std::cout << "Knights from team B: " << save.getTeamB().at(0) << std::endl;
	std::cout << "Warriors from team B: " << save.getTeamB().at(1) << std::endl;
	std::cout << "Archers from team B: " << save.getTeamB().at(2) << std::endl;
	std::cout << "Riders from team B: " << save.getTeamB().at(3) << std::endl;
	std::cout << "Mages from team B: " << save.getTeamB().at(4) << std::endl;*/

	//Tworzenie  planszy NxN
	std::cout << "TO ROBIE" << std::endl;
	for (unsigned int i = 0; i < save.getMapSize(); i++) {
		for (unsigned int j = 0; j < save.getMapSize(); j++) {
			std::cout << i << " " << j << std::endl;
			if ((i == 0) && (j == 0)) {
				first = new Square;
				first->setTexture(mapTile);
				first->setPosition(0, 0);
			}
			else if ((i == 0) && (j == 1)){
				prev = new Square;
				prev->setTexture(mapTile);
				prev->setPosition(64, 0);
				first->setRight(prev);
				prev->setLeft(first);
			}
			else if ((i == 0) && (j > 1)) {
				temp = new Square;
				temp->setTexture(mapTile);
				temp->setPosition((float)j*64, 0);
				temp->setLeft(prev);
				prev->setRight(temp);
				prev = temp;
			}
			else if ((i > 0) && (j == 0)) {
				prev = new Square;
				prev->setTexture(mapTile);
				prev->setPosition((float)j * 64, (float)i * 64);
				temp = first;
				for (unsigned int k = 1; k < i; k++) {
					temp = temp->getDown();
				}
				temp->setDown(prev);
				prev->setUp(temp);
			}
			else {
				temp = new Square;
				temp->setTexture(mapTile);
				temp->setPosition((float)j * 64, (float)i * 64);
				temp->setLeft(prev);
				prev->setRight(temp);
				temp->setUp(prev->getUp()->getRight());
				temp->getUp()->setDown(temp);
				prev = temp;
			}
		}
	}
	temp = nullptr;
	prev = nullptr;
	std::cout << save.getTeamA().at(0) << std::endl;
	std::cout << save.getTeamA().at(4) << std::endl;
	std::cout << save.getTeamB().at(0) << std::endl;
	std::cout << save.getTeamB().at(4) << std::endl;
	KnA = save.getTeamA().at(0);
	WaA = save.getTeamA().at(1);
	ArA = save.getTeamA().at(2);
	RiA = save.getTeamA().at(3);
	MaA = save.getTeamA().at(4);
	KnB = save.getTeamB().at(0);
	WaB = save.getTeamB().at(1);
	ArB = save.getTeamB().at(2);
	RiB = save.getTeamB().at(3);
	MaB = save.getTeamB().at(4);
	changeUnitSelect(unitType);
	//LOOP FOR PLACING TEAMS

	while (true) {
		window.clear(sf::Color::Black);
		window.pollEvent(event);
		temp = first;
		for (unsigned int i = 0; i < save.getMapSize(); i++) {
			for (unsigned int j = 0; j < save.getMapSize(); j++) {
				window.draw(*temp);
				if (temp->getUnit() != nullptr)
					window.draw(*temp->getUnit());
				temp = temp->getRight();
			}
			temp = first;
			for (unsigned int j = 0; j < i+1; j++) {
				temp = temp->getDown();
			}
		}
		text1.setPosition(view.getCenter().x, view.getCenter().y + 300);
		text2.setPosition(view.getCenter().x + 200, view.getCenter().y + 250);
		selectedUnit.setPosition(view.getCenter().x + 384, view.getCenter().y + 272);
		window.draw(selectedUnit);
		window.draw(text1);
		window.draw(text2);
		//if ((event.type == sf::Event::MouseButtonPressed) && (mouseHold != true)) {
		if ((mouse.isButtonPressed(sf::Mouse::Left)) && (mouseHold != true)) {
			temp = first;
			nullSquare = false;
			for (int i = 0; i < (int)((mouse.getPosition(window).x + view.getCenter().x - 512) / 64); i++) {
				if (temp->getRight() == nullptr) {
					nullSquare = true;
					break;
				}
				temp = temp->getRight();
			}
			for (int i = 0; i < (int)((mouse.getPosition(window).y + view.getCenter().y - 400) / 64); i++) {
				if ((temp->getDown() == nullptr) || (nullSquare)) {
					nullSquare = true;
					break;
				}
				temp = temp->getDown();
			}
			if (!nullSquare) {
				if (actual == nullptr) {
					actual = temp;
					temp->touch();
					temp->setTexture(mapTileTouched);
				}
				else {
					if (actual == temp) {
						switch (unitType) {
						case KnightA:
							temp->putUnit(new Knight(true)); // true for A team
							setUpUnit(temp, knightImA);
							KnA--;
							if (KnA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(KnA));
							break;
						case WarriorA:
							temp->putUnit(new Warrior);
							setUpUnit(temp, warriorImA);
							WaA--;
							if (WaA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(WaA));
							break;
						case ArcherA:
							temp->putUnit(new Archer);
							setUpUnit(temp, archerImA);
							ArA--;
							if (ArA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(ArA));
							break;
						case RiderA:
							temp->putUnit(new Rider);
							setUpUnit(temp, riderImA);
							RiA--;
							if (RiA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(RiA));
							break;
						case MageA:
							temp->putUnit(new Mage);
							setUpUnit(temp, mageImA);
							MaA--;
							if (MaA == 0) changeTeamSelect();
							else text2.setString(std::to_string(MaA));
							break;
						case KnightB:
							temp->putUnit(new Knight);
							setUpUnit(temp, knightImA);
							KnA--;
							if (KnA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(KnA));
							break;
						case WarriorB:
							temp->putUnit(new Warrior);
							setUpUnit(temp, warriorImA);
							WaA--;
							if (WaA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(WaA));
							break;
						case ArcherB:
							temp->putUnit(new Archer);
							setUpUnit(temp, archerImA);
							ArA--;
							if (ArA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(ArA));
							break;
						case RiderB:
							temp->putUnit(new Rider);
							setUpUnit(temp, riderImA);
							RiA--;
							if (RiA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(RiA));
							break;
						case MageB:
							temp->putUnit(new Mage);
							setUpUnit(temp, mageImA);
							MaA--;
							if (MaA == 0) changeTeamSelect();
							else text2.setString(std::to_string(MaA));
							break;
						}
						temp->touch();
						temp->setTexture(mapTile);
						actual = nullptr;
					}
					else {
						temp->touch();
						temp->setTexture(mapTileTouched);
						actual->touch();
						actual->setTexture(mapTile);
						actual = temp;
					}
				}
				/*if (temp->isTouched() == false) {
					temp->setTexture(mapTileTouched);
				}
				else {
					temp->setTexture(mapTile);
				}
				temp->touch();
				if ((actual != temp) && (actual != nullptr)) {

				}*/
			}
			//std::cout << mouse.getPosition(window).x << " " << mouse.getPosition(window).y << std::endl;
			mouseHold = true;
		}
		if (mouse.isButtonPressed(sf::Mouse::Right)) {
			if (holding) {
				/*if (mouse.getPosition(window).x > view.getCenter().x) x = 2;
				else if (mouse.getPosition(window).x < view.getCenter().x) x = -2;
				else x = 0;
				if (mouse.getPosition(window).y > view.getCenter().y) y = 2;
				else if (mouse.getPosition(window).y < view.getCenter().y) y = -2;
				else y = 0;*/
				//std::cout << prevPos.x - mouse.getPosition(window).x << " " << prevPos.y - mouse.getPosition(window).y << std::endl;
				//view.move((float)(prevPos.x - mouse.getPosition(window).x), (float)(prevPos.y - mouse.getPosition(window).y));
				//view.move(x, y);
				view.setCenter((sf::Vector2f)mouse.getPosition(window));
				window.setView(view);
				//prevPos = mouse.getPosition();
				//window.getView().move(2, 3);
				//view.move(2,3);
			}
			else {
				//prevPos = mouse.getPosition();
				holding = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
			holding = false;
		}
		window.display();
	}
}

void BattlegroundScene::changeTeamSelect()
{
	text1.setString("Gracz B rozstawia jednostki");
}

void BattlegroundScene::changeUnitSelect(UnitType& unit)
{
	switch (unit) {
	case KnightA:
		std::cout << "Knight" << std::endl;
		if (KnA != 0) {
			selectedUnit.setTexture(knightImA);
			text2.setString(std::to_string(KnA));
			break;
		}
	case WarriorA:
		std::cout << "Warrior" << std::endl;
		if (WaA != 0) {
			unitType = WarriorA;
			selectedUnit.setTexture(warriorImA);
			text2.setString(std::to_string(WaA));
			break;
		}
	case ArcherA:
		std::cout << "Archer" << std::endl;
		if (ArA != 0) {
			unitType = ArcherA;
			selectedUnit.setTexture(archerImA);
			text2.setString(std::to_string(ArA));
			break;
		}
	case RiderA:
		std::cout << "Rider" << std::endl;
		if (RiA != 0) {
			unitType = RiderA;
			selectedUnit.setTexture(riderImA);
			text2.setString(std::to_string(RiA));
			break;
		}
	case MageA:
		std::cout << "Mage" << std::endl;
		if (MaA != 0) {
			unitType = MageA;
			selectedUnit.setTexture(mageImA);
			text2.setString(std::to_string(MaA));
			break;
		}
		else changeTeamSelect();
		break;
	}
}

void BattlegroundScene::setUpUnit(Square *temp, sf::Texture & texture)
{
	temp->getUnit()->setTexture(texture);
	temp->getUnit()->setPosition(temp->getPosition());
	temp->getUnit()->setScale(0.5, 0.5);
}

BattlegroundScene::BattlegroundScene()
{
	mapTile.loadFromFile("include/images/mapTile.png");
	mapTileTouched.loadFromFile("include/images/mapTileTouched.png");
	temp = nullptr;
	prev = nullptr;
	actual = nullptr;
	holding = false;
	unitType = KnightA;
	text1.setFont(font);
	text2.setFont(font);
	knightImA.loadFromFile("include/characters/knight.png");
	warriorImA.loadFromFile("include/characters/warrior.png");
	archerImA.loadFromFile("include/characters/archer.png");
	riderImA.loadFromFile("include/characters/rider.png");
	mageImA.loadFromFile("include/characters/mage.png");
	knightImB.loadFromFile("include/characters/knightB.png");
	warriorImB.loadFromFile("include/characters/warriorB.png");
	archerImB.loadFromFile("include/characters/archerB.png");
	riderImB.loadFromFile("include/characters/riderB.png");
	mageImB.loadFromFile("include/characters/mageB.png");
}


BattlegroundScene::~BattlegroundScene()
{
}
