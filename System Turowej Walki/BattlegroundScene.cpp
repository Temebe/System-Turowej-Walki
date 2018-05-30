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
	for (unsigned int i = 0; i < save.getMapSize(); i++) {
		for (unsigned int j = 0; j < save.getMapSize(); j++) {
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

	while (selectingMode) {
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
		if ((mouse.isButtonPressed(sf::Mouse::Left)) && (mouseHold != true)) {
			temp = first;
			nullSquare = false;
			clickedPos.x = 1;
			for (int i = 0; i < (int)((mouse.getPosition(window).x + view.getCenter().x - 512) / 64); i++) {
				if (temp->getRight() == nullptr) {
					nullSquare = true;
					break;
				}
				clickedPos.x = clickedPos.x + 1;
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
					if (temp != nullptr) {
						if ((teamASelecting) && (clickedPos.x > save.getMapSize() / 2)) {
						}
						else if ((!teamASelecting) && (clickedPos.x <= (save.getMapSize() + 1) / 2)) {
						}
						else if (temp->getUnit() == nullptr) {
							actual = temp;
							temp->touch();
							temp->setTexture(mapTileTouched);
						}
					}
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
							temp->putUnit(new Warrior(true));
							setUpUnit(temp, warriorImA);
							WaA--;
							if (WaA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(WaA));
							break;
						case ArcherA:
							temp->putUnit(new Archer(true));
							setUpUnit(temp, archerImA);
							ArA--;
							if (ArA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(ArA));
							break;
						case RiderA:
							temp->putUnit(new Rider(true));
							setUpUnit(temp, riderImA);
							RiA--;
							if (RiA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(RiA));
							break;
						case MageA:
							temp->putUnit(new Mage(true));
							setUpUnit(temp, mageImA);
							MaA--;
							if (MaA == 0) changeTeamSelect();
							else text2.setString(std::to_string(MaA));
							break;
						case KnightB:
							temp->putUnit(new Knight(false)); // false for B team
							setUpUnit(temp, knightImB);
							KnB--;
							if (KnB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(KnB));
							break;
						case WarriorB:
							temp->putUnit(new Warrior(false));
							setUpUnit(temp, warriorImB);
							WaB--;
							if (WaB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(WaB));
							break;
						case ArcherB:
							temp->putUnit(new Archer(false));
							setUpUnit(temp, archerImB);
							ArB--;
							if (ArB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(ArB));
							break;
						case RiderB:
							temp->putUnit(new Rider(false));
							setUpUnit(temp, riderImB);
							RiB--;
							if (RiB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(RiB));
							break;
						case MageB:
							temp->putUnit(new Mage(false));
							setUpUnit(temp, mageImB);
							MaB--;
							if (MaB == 0) changeTeamSelect();
							else text2.setString(std::to_string(MaB));
							break;
						}
						temp->touch();
						temp->setTexture(mapTile);
						actual = nullptr;
					}
					else {
						if (temp->getUnit() != nullptr) {
							actual->touch();
							actual->setTexture(mapTile);
							actual = nullptr;
						}
						else {
							if (temp != nullptr) {
								if ((teamASelecting) && (clickedPos.x > save.getMapSize() / 2)) {
									std::cout << "first if" << std::endl;
									actual->touch();
									actual->setTexture(mapTile);
									actual = nullptr;
								}
								else if ((!teamASelecting) && (clickedPos.x <= (save.getMapSize() + 1) / 2)) {
									std::cout << "second if" << std::endl;
									actual->touch();
									actual->setTexture(mapTile);
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
						}
					}
				}
			}
			mouseHold = true;
		}
		if (mouse.isButtonPressed(sf::Mouse::Right)) {
			if (holding) {
				view.setCenter((sf::Vector2f)mouse.getPosition(window));
				window.setView(view);
			}
			else {
				holding = true;
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				return 5;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
			holding = false;
		}
		window.display();
	}

	//Playing mode

	while (1) {
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
			for (unsigned int j = 0; j < i + 1; j++) {
				temp = temp->getDown();
			}
		}
		text1.setPosition(view.getCenter().x, view.getCenter().y + 300);
		text2.setPosition(view.getCenter().x + 200, view.getCenter().y + 250);
		selectedUnit.setPosition(view.getCenter().x + 384, view.getCenter().y + 272);
		window.draw(text1);
		window.draw(text2);
		if ((mouse.isButtonPressed(sf::Mouse::Left)) && (mouseHold != true))	{
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
					if (temp != nullptr) {
						if (temp->getUnit() == nullptr) {
							actual = temp;
							temp->touch();
							temp->setTexture(mapTileTouched);
						}
					}
				}
				else {
					if (actual == temp) {
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
			}
			mouseHold = true;
		}
		if (mouse.isButtonPressed(sf::Mouse::Right)) {
			if (holding) {
				view.setCenter((sf::Vector2f)mouse.getPosition(window));
				window.setView(view);
			}
			else {
				holding = true;
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				return 5;
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
	unitType = KnightB;
	changeUnitSelect(unitType);
	teamASelecting = false;
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
	case KnightB:
		std::cout << "KnightB" << std::endl;
		if (KnB != 0) {
			unitType = KnightB;
			selectedUnit.setTexture(knightImB);
			text2.setString(std::to_string(KnB));
			break;
		}
	case WarriorB:
		std::cout << "WarriorB" << std::endl;
		if (WaB != 0) {
			unitType = WarriorB;
			selectedUnit.setTexture(warriorImB);
			text2.setString(std::to_string(WaB));
			break;
		}
	case ArcherB:
		std::cout << "ArcherB" << std::endl;
		if (ArB != 0) {
			unitType = ArcherB;
			selectedUnit.setTexture(archerImB);
			text2.setString(std::to_string(ArB));
			break;
		}
	case RiderB:
		std::cout << "RiderB" << std::endl;
		if (RiB != 0) {
			unitType = RiderB;
			selectedUnit.setTexture(riderImB);
			text2.setString(std::to_string(RiB));
			break;
		}
	case MageB:
		std::cout << "MageB" << std::endl;
		if (MaB != 0) {
			unitType = MageB;
			selectedUnit.setTexture(mageImB);
			text2.setString(std::to_string(MaB));
			break;
		}
	default:
		text1.setString("Koniec");
		text2.setString("0");
		selectingMode = false;
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
	selectingMode = true;
	teamASelecting = true;
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
	text1.setString("Gracz A rozstawia jednostki");
}


BattlegroundScene::~BattlegroundScene()
{
}
