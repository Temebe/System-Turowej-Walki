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
				if (temp->getUnit() != nullptr) {
					window.draw(*temp->getUnit());
				}
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
							temp->putUnit(new Knight(true, &knightsA)); // true for A team
							temp->getUnit()->setType(KnightA);
							knightsA.push_back(temp->getUnit());
							setUpUnit(temp, knightImA);
							KnA--;
							if (KnA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(KnA));
							break;
						case WarriorA:
							temp->putUnit(new Warrior(true, &warriorsA));
							temp->getUnit()->setType(WarriorA);
							warriorsA.push_back(temp->getUnit());
							setUpUnit(temp, warriorImA);
							WaA--;
							if (WaA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(WaA));
							break;
						case ArcherA:
							temp->putUnit(new Archer(true, &archersA));
							temp->getUnit()->setType(ArcherA);
							archersA.push_back(temp->getUnit());
							setUpUnit(temp, archerImA);
							ArA--;
							if (ArA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(ArA));
							break;
						case RiderA:
							temp->putUnit(new Rider(true, &ridersA));
							temp->getUnit()->setType(RiderA);
							ridersA.push_back(temp->getUnit());
							setUpUnit(temp, riderImA);
							RiA--;
							if (RiA == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(RiA));
							break;
						case MageA:
							temp->putUnit(new Mage(true, &magesA));
							temp->getUnit()->setType(MageA);
							magesA.push_back(temp->getUnit());
							setUpUnit(temp, mageImA);
							MaA--;
							if (MaA == 0) changeTeamSelect();
							else text2.setString(std::to_string(MaA));
							break;
						case KnightB:
							temp->putUnit(new Knight(false, &knightsB)); // false for B team
							temp->getUnit()->setType(KnightB);
							knightsB.push_back(temp->getUnit());
							setUpUnit(temp, knightImB);
							KnB--;
							if (KnB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(KnB));
							break;
						case WarriorB:
							temp->putUnit(new Warrior(false, &warriorsB));
							temp->getUnit()->setType(WarriorB);
							warriorsB.push_back(temp->getUnit());
							setUpUnit(temp, warriorImB);
							WaB--;
							if (WaB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(WaB));
							break;
						case ArcherB:
							temp->putUnit(new Archer(false, &archersB));
							temp->getUnit()->setType(ArcherB);
							archersB.push_back(temp->getUnit());
							setUpUnit(temp, archerImB);
							ArB--;
							if (ArB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(ArB));
							break;
						case RiderB:
							temp->putUnit(new Rider(false, &ridersB));
							temp->getUnit()->setType(RiderB);
							ridersB.push_back(temp->getUnit());
							setUpUnit(temp, riderImB);
							RiB--;
							if (RiB == 0) changeUnitSelect(unitType);
							else text2.setString(std::to_string(RiB));
							break;
						case MageB:
							temp->putUnit(new Mage(false, &magesB));
							temp->getUnit()->setType(MageB);
							magesB.push_back(temp->getUnit());
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
	text1.setString("Tura gracza A");
	selectedUnit.setTexture(knightImA);
	unitType = KnightA;
	if (knightsA.size() == 0) changeUnitTurn(unitType);
	//teamASelecting = true;

	while (1) {
		window.clear(sf::Color::Black);
		window.pollEvent(event);
		temp = first;
		for (unsigned int i = 0; i < save.getMapSize(); i++) {
			for (unsigned int j = 0; j < save.getMapSize(); j++) {
				window.draw(*temp);
				if (temp->getUnit() != nullptr) {
					window.draw(*temp->getUnit());
					window.draw(*temp->getUnit()->getHPBar());
				}
				temp = temp->getRight();
			}
			temp = first;
			for (unsigned int j = 0; j < i + 1; j++) {
				temp = temp->getDown();
			}
		}
		text1.setPosition(view.getCenter().x, view.getCenter().y + 300);
		selectedUnit.setPosition(view.getCenter().x + 384, view.getCenter().y + 272);
		window.draw(text1);
		window.draw(selectedUnit);
		if (unitUI) {
			move.setPosition(view.getCenter().x - 512, view.getCenter().y + 300);
			fight.setPosition(view.getCenter().x - 432, view.getCenter().y + 300);
			idle.setPosition(view.getCenter().x - 352, view.getCenter().y + 300);
			window.draw(move);
			window.draw(fight);
			window.draw(idle);
		}
		if (event.type == sf::Event::KeyPressed) {
			if (unitUI)unitUICheck(event);
			if (event.key.code == sf::Keyboard::X) {
				if (turnType == chooseDirection) {
					findWay(actual, actual->getUnit()->getTempMovement(), 0, false);
				}
				if (turnType == chooseTarget) {
					findEnemy(actual, actual->getUnit()->getAttackRange(), false, true);
				}
				if (actual != nullptr) {
					unitUI = false;
					actual->setTexture(mapTile);
					actual->touch();
					actual = nullptr;
					turnType = nothing;
				}
			}
			if (event.key.code == sf::Keyboard::Escape) {
				return 5;
			}
		}
		if ((mouse.isButtonPressed(sf::Mouse::Left)) && (mouseHold != true)) {
			temp = first;
			nullSquare = false;
			if (unitUI) unitUICheck(window, view);
			if (turnType == nothing) nothingTurn(window, view);
			if (turnType == chooseDirection) chooseDirectionTurn(window, view);
			if (turnType == chooseTarget) chooseTargetTurn(window, view);
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
		std::cout << "USTAWILEM" << std::endl;
		teamASelecting = true;
		break;
	}
}

/*void BattlegroundScene::changeUnitTurn(UnitType & unit)
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
		std::cout << "USTAWILEM" << std::endl;
		teamASelecting = true;
		break;
	}
}*/

void BattlegroundScene::changeUnitTurn(UnitType& type) {
	if (type == KnightA) {
		for (int i = 0; i < knightsA.size(); i++) {
			std::cout << "Knight! " << i << std::endl;
			if (!knightsA.at(i)->hadTurn()) {
				return;
			}
		}
		type = KnightB;
		text1.setString("Tura gracza B");
		selectedUnit.setTexture(knightImB);
	}
	if (type == KnightB) {
		for (int i = 0; i < knightsB.size(); i++) {
			if (!knightsB.at(i)->hadTurn()) {
				return;
			}
		}
		type = WarriorA;
		text1.setString("Tura gracza A");
		selectedUnit.setTexture(warriorImA);
	}
	if (type == WarriorA) {
		for (int i = 0; i < warriorsA.size(); i++) {
			if (!warriorsA.at(i)->hadTurn()) {
				return;
			}
		}
		type = WarriorB;
		text1.setString("Tura gracza B");
		selectedUnit.setTexture(warriorImB);
	}
	if (type == WarriorB) {
		for (int i = 0; i < warriorsB.size(); i++) {
			if (!warriorsB.at(i)->hadTurn()) {
				return;
			}
		}
		type = ArcherA;
		text1.setString("Tura gracza A");
		selectedUnit.setTexture(archerImA);
	}
	if (type == ArcherA) {
		for (int i = 0; i < archersA.size(); i++) {
			if (!archersA.at(i)->hadTurn()) {
				return;
			}
		}
		type = ArcherB;
		text1.setString("Tura gracza B");
		selectedUnit.setTexture(archerImB);
	}
	if (type == ArcherB) {
		for (int i = 0; i < archersB.size(); i++) {
			if (!archersB.at(i)->hadTurn()) {
				return;
			}
		}
		type = RiderA;
		text1.setString("Tura gracza A");
		selectedUnit.setTexture(riderImA);
	}
	if (type == RiderA) {
		for (int i = 0; i < ridersA.size(); i++) {
			if (!ridersA.at(i)->hadTurn()) {
				return;
			}
		}
		type = RiderB;
		text1.setString("Tura gracza B");
		selectedUnit.setTexture(riderImB);
	}
	if (type == RiderB) {
		for (int i = 0; i < ridersB.size(); i++) {
			if (!ridersB.at(i)->hadTurn()) {
				return;
			}
		}
		type = MageA;
		text1.setString("Tura gracza A");
		selectedUnit.setTexture(mageImA);
	}
	if (type == MageA) {
		for (int i = 0; i < magesA.size(); i++) {
			if (!magesA.at(i)->hadTurn()) {
				return;
			}
		}
		type = MageB;
		text1.setString("Tura gracza B");
		selectedUnit.setTexture(mageImB);
	}
	if (type == MageB) {
		for (int i = 0; i < magesB.size(); i++) {
			if (!magesB.at(i)->hadTurn()) {
				return;
			}
		}
		type = KnightA;
		text1.setString("Tura gracza A");
		selectedUnit.setTexture(knightImA);
		setNewTurn();
		changeUnitTurn(unitType);
	}
}

void BattlegroundScene::setUpUnit(Square *temp, sf::Texture & texture)
{
	temp->getUnit()->setTexture(texture);
	temp->getUnit()->setPosition(temp->getPosition());
	temp->getUnit()->setScale(0.5, 0.5);
	temp->getUnit()->setHPBar(new sf::Sprite); //something is not yes
	temp->getUnit()->setHPBarTexture(hpbarIm);
	temp->getUnit()->getHPBar()->setScale(1, 0.4);
	temp->getUnit()->getHPBar()->setPosition(temp->getUnit()->getPosition().x, (double)temp->getUnit()->getPosition().y + ((double)temp->getUnit()->getTexture()->getSize().y * 0.75 * 0.5));
}

bool BattlegroundScene::isHisTurn(Square * temp)
{
	return ((unitType == temp->getUnit()->getType()) && (!temp->getUnit()->hadTurn()));
}

Square * BattlegroundScene::findWay(Square * temp, int movement, int iteration, bool val)
{
	if (temp == nullptr) return nullptr;
	if (movement != 0) {
		if (temp->getUp() != nullptr) {
			if ((temp->getUp()->getUnit() == nullptr) || (!val)) {
				findWay(temp->getUp(), movement - 1, iteration + 1, val);
			}
		}
		if (temp->getDown() != nullptr) {
			if ((temp->getDown()->getUnit() == nullptr) || (!val)) {
				findWay(temp->getDown(), movement - 1, iteration + 1, val);
			}
		}
		if (temp->getLeft() != nullptr) {
			if ((temp->getLeft()->getUnit() == nullptr) || (!val)) {
				findWay(temp->getLeft(), movement - 1, iteration + 1, val);
			}
		}
		if (temp->getRight() != nullptr) {
			if ((temp->getRight()->getUnit() == nullptr) || (!val)) {
				findWay(temp->getRight(), movement - 1, iteration + 1, val);
			}
		}
	}
	if (iteration != 0) {
		if (val) {
			temp->setTexture(mapTileAble);
			if (temp->getMovementCost() > iteration) temp->setMovementCost(iteration);
		}
		else {
			temp->setTexture(mapTile);
			temp->setMovementCost(INT_MAX);
		}
		temp->setAble(val);
	}
	/*if (temp->getUp()->getUnit() == nullptr) {
		if(val)temp->setTexture(mapTileAble);
		else temp->setTexture(mapTile);
		temp->getUp()->setAble(val);
	}*/
}

/*Square * BattlegroundScene::findEnemy(Square * temp, int attackRange, bool val, bool firstIteration)
{
	if (temp == nullptr) return nullptr;
	if (attackRange != 0) {
		if (temp->getUp() != nullptr) {
			if (temp->getUp()->getRight() != nullptr) {
				if ((temp->getUp()->getRight()->getUnit() != nullptr) || (!val)) {
					findEnemy(temp->getUp()->getRight(), attackRange - 1, val, false);
				}
			}
			if (temp->getUp()->getLeft() != nullptr) {
				if ((temp->getUp()->getLeft()->getUnit() != nullptr) || (!val)) {
					findEnemy(temp->getUp()->getLeft(), attackRange - 1, val, false);
				}
			}
			if ((temp->getUp()->getUnit() != nullptr) || (!val)) {
				findEnemy(temp->getUp(), attackRange - 1, val, false);
			}
		}
		if (temp->getDown() != nullptr) {
			if (temp->getDown()->getRight() != nullptr) {
				if ((temp->getDown()->getRight()->getUnit() != nullptr) || (!val)) {
					findEnemy(temp->getDown()->getRight(), attackRange - 1, val, false);
				}
			}
			if (temp->getDown()->getLeft() != nullptr) {
				if ((temp->getDown()->getLeft()->getUnit() != nullptr) || (!val)) {
					findEnemy(temp->getDown()->getLeft(), attackRange - 1, val, false);
				}
			}
			if ((temp->getDown()->getUnit() != nullptr) || (!val)) {
				findEnemy(temp->getDown(), attackRange - 1, val, false);
			}
		}
		if (temp->getLeft() != nullptr) {
			if ((temp->getLeft()->getUnit() != nullptr) || (!val)) {
				findEnemy(temp->getLeft(), attackRange - 1, val, false);
			}
		}
		if (temp->getRight() != nullptr) {
			if ((temp->getRight()->getUnit() != nullptr) || (!val)) {
				findEnemy(temp->getRight(), attackRange - 1, val, false);
			}
		}
	}
	if (!firstIteration) {
		if (val) {
			temp->setTexture(mapTileAble);
		}
		else {
			temp->setTexture(mapTile);
		}
		if(temp->getUnit() != nullptr) temp->getUnit()->setPropTarget(val);
	}
}*/ //Previous version

Square * BattlegroundScene::findEnemy(Square * temp, int attackRange, bool val, bool firstIteration)
{
	if (temp == nullptr) return nullptr;
	if (attackRange != 0) {
		if (temp->getUp() != nullptr) {
			if (temp->getUp()->getRight() != nullptr) {
				findEnemy(temp->getUp()->getRight(), attackRange - 1, val, false);
			}
			if (temp->getUp()->getLeft() != nullptr) {
				findEnemy(temp->getUp()->getLeft(), attackRange - 1, val, false);
			}
			findEnemy(temp->getUp(), attackRange - 1, val, false);
		}
		if (temp->getDown() != nullptr) {
			if (temp->getDown()->getRight() != nullptr) {
				findEnemy(temp->getDown()->getRight(), attackRange - 1, val, false);
			}
			if (temp->getDown()->getLeft() != nullptr) {
				findEnemy(temp->getDown()->getLeft(), attackRange - 1, val, false);
			}
			findEnemy(temp->getDown(), attackRange - 1, val, false);
		}
		if (temp->getLeft() != nullptr) {
			findEnemy(temp->getLeft(), attackRange - 1, val, false);
		}
		if (temp->getRight() != nullptr) {
			findEnemy(temp->getRight(), attackRange - 1, val, false);
		}
	}
	if (!firstIteration) {
		if (val) {
			temp->setTexture(mapTileAble);
		}
		else {
			temp->setTexture(mapTile);
		}
		if (temp->getUnit() != nullptr) temp->getUnit()->setPropTarget(val);
	}
}

void BattlegroundScene::nothingTurn(sf::RenderWindow& window, sf::View& view)
{
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
				if ((temp->getUnit() != nullptr) && (isHisTurn(temp))) {
					unitUI = true;
					actual = temp;
					temp->touch();
					temp->setTexture(mapTileTouched);
				}
			}
		}
		else {
			if (actual == temp) {
				unitUI = false;
				temp->touch();
				temp->setTexture(mapTile);
				actual = nullptr;
			}
			else {
				if (temp->getUnit() == nullptr) {
					unitUI = false;
					actual->touch();
					actual->setTexture(mapTile);
					actual = nullptr;
				}
				else if (isHisTurn(temp)) {
					temp->touch();
					temp->setTexture(mapTileTouched);
					actual->touch();
					actual->setTexture(mapTile);
					actual = temp;
				}
				else {
					unitUI = false;
					actual->touch();
					actual->setTexture(mapTile);
					actual = nullptr;
				}
			}
		}
	}
}

void BattlegroundScene::chooseDirectionTurn(sf::RenderWindow & window, sf::View & view)
{
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
		if (actual == temp) { //cancellation of choosing path
			temp->touch();
			temp->setTexture(mapTile);
			findWay(actual, actual->getUnit()->getTempMovement(), 0, false);
		}
		else {
			if (temp->getUnit() == nullptr) { //choosing direction
				if (temp->isAbleToMove()) {
					moveUnit(actual, temp, *actual->getUnit());
					findWay(actual, temp->getUnit()->getTempMovement() + temp->getMovementCost(), 0, false);
					checkIfUnitFinished(temp->getUnit());
				}
			}
			else {
				temp->touch();
				temp->setTexture(mapTileTouched);
				actual->touch();
				actual->setTexture(mapTile);
				findWay(actual, actual->getUnit()->getTempMovement(), 0, false);
			}
		}
		actual->setTexture(mapTile);
		actual->touch();
		actual = nullptr;
		turnType = nothing;
	}
}

void BattlegroundScene::chooseTargetTurn(sf::RenderWindow & window, sf::View & view)
{
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
		if (temp->getUnit() != nullptr) {
			if (temp->getUnit()->isPropTarget()) {
				actual->getUnit()->attack(temp);
				if (temp->getUnit() == nullptr) {
					if (checkIfWon()) {
						turnType = won;
						return;
					}
				}
				else checkIfUnitFinished(actual->getUnit());
			}
		}
		findEnemy(actual, actual->getUnit()->getAttackRange(), false, true);
		actual->setTexture(mapTile);
		actual->touch();
		actual = nullptr;
		turnType = nothing;
	}
}

void BattlegroundScene::setNewTurn()
{
	for (int i = 0; i < knightsA.size(); i++) {
		knightsA.at(i)->prepareForTurn();
	}
	for (int i = 0; i < knightsB.size(); i++) {
		knightsB.at(i)->prepareForTurn();
	}
	for (int i = 0; i < warriorsA.size(); i++) {
		warriorsA.at(i)->prepareForTurn();
	}
	for (int i = 0; i < warriorsB.size(); i++) {
		warriorsB.at(i)->prepareForTurn();
	}
	for (int i = 0; i < archersA.size(); i++) {
		archersA.at(i)->prepareForTurn();
	}
	for (int i = 0; i < archersB.size(); i++) {
		archersB.at(i)->prepareForTurn();
	}
	for (int i = 0; i < magesA.size(); i++) {
		magesA.at(i)->prepareForTurn();
	}
	for (int i = 0; i < magesB.size(); i++) {
		magesB.at(i)->prepareForTurn();
	}
}

void BattlegroundScene::unitUICheck(sf::RenderWindow & window, sf::View& view)
{
	if (fight.isMouseOver(mouse, window)) {
		if (actual->getUnit()->canAttack()) {
			findEnemy(actual, actual->getUnit()->getAttackRange(), true, true);
			turnType = chooseTarget;
			unitUI = false;
			nullSquare = true;
		}
		else {
			std::cout << "nope" << std::endl;
			//Add info to player
		}
	}
	else if (move.isMouseOver(mouse, window, view)) {
		if (actual->getUnit()->isMovable()) {
			findWay(actual, actual->getUnit()->getTempMovement(), 0, true);
			turnType = chooseDirection;
			unitUI = false;
			nullSquare = true;
		}
		else {
			std::cout << "nope" << std::endl;
		}
	}
	else if (idle.isMouseOver(mouse, window, view)) {
		actual->getUnit()->setTurn(true);
		changeUnitTurn(unitType);
		turnType = nothing;
		unitUI = false;
		nullSquare = true;
		actual->setTexture(mapTile);
		actual = nullptr;
	}
}

void BattlegroundScene::unitUICheck(sf::Event & event)
{
	if (event.key.code == sf::Keyboard::S) {
		if (actual->getUnit()->canAttack()) {
			findEnemy(actual, actual->getUnit()->getAttackRange(), true, true);
			turnType = chooseTarget;
			unitUI = false;
			nullSquare = true;
		}
		else {
			std::cout << "nope" << std::endl;
			//Add info to player
		}
	}
	else if (event.key.code == sf::Keyboard::A) {
		if (actual->getUnit()->isMovable()) {
			findWay(actual, actual->getUnit()->getTempMovement(), 0, true);
			turnType = chooseDirection;
			unitUI = false;
			nullSquare = true;
		}
		else {
			std::cout << "nope" << std::endl;
		}
	}
	else if (event.key.code == sf::Keyboard::D) {
		actual->getUnit()->setTurn(true);
		changeUnitTurn(unitType);
		turnType = nothing;
		unitUI = false;
		nullSquare = true;
		actual->setTexture(mapTile);
		actual = nullptr;
	}
}

void BattlegroundScene::checkIfUnitFinished(Unit * tempUnit)
{
	if ((tempUnit->isMovable() == false) && (tempUnit->canAttack() == false)) {
		tempUnit->setTurn(true);
		changeUnitTurn(unitType);
		turnType = nothing;
	}
}

bool BattlegroundScene::checkIfWon()
{
	bool AEmpty = true, BEmpty = true;
	if (knightsA.size() != 0) AEmpty = false;
	else if (warriorsA.size() != 0) AEmpty = false;
	else if (archersA.size() != 0) AEmpty = false;
	else if (magesA.size() != 0) AEmpty = false;
	else if (ridersA.size() != 0) AEmpty = false;
	if (knightsB.size() != 0) BEmpty = false;
	else if (warriorsB.size() != 0) BEmpty = false;
	else if (archersB.size() != 0) BEmpty = false;
	else if (magesB.size() != 0) BEmpty = false;
	else if (ridersB.size() != 0) BEmpty = false;
	if ((AEmpty == true) && (BEmpty == true)) {
		text1.setString("REMIS REMIS REMIS");
	}
	if (AEmpty == true) {
		text1.setString("TEAM B WINS");
	}
	if (BEmpty == true) {
		text1.setString("TEAM A WINS");
	}
	return (AEmpty || BEmpty);
}

void BattlegroundScene::moveUnit(Square * location, Square * destination, Unit& unit)
{
	unit.setPosition(destination->getPosition());
	unit.getHPBar()->setPosition(unit.getPosition().x, (double)unit.getPosition().y + ((double)unit.getTexture()->getSize().y * 0.75 * 0.5));
	if ((unitType == RiderA) || (unitType == RiderB)) unit.setMovable(false);
	unit.lossTempMovement(destination->getMovementCost());
	location->putUnit(nullptr);
	destination->putUnit(&unit);
}

BattlegroundScene::BattlegroundScene()
{
	mapTile.loadFromFile("include/images/mapTile.png");
	mapTileTouched.loadFromFile("include/images/mapTileTouched.png");
	mapTileAble.loadFromFile("include/images/mapTileAble.png");
	hpbarIm.loadFromFile("include/images/hpbar.png");
	temp = nullptr;
	prev = nullptr;
	actual = nullptr;
	holding = false;
	selectingMode = true;
	teamASelecting = true;
	turnType = nothing;
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
	moveIm.loadFromFile("include/buttons/move.png");
	idleIm.loadFromFile("include/buttons/idle.png");
	fightIm.loadFromFile("include/buttons/fight.png");
	move.setTexture(moveIm);
	idle.setTexture(idleIm);
	fight.setTexture(fightIm);
}


BattlegroundScene::~BattlegroundScene()
{
}
