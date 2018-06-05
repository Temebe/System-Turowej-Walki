#include "stdafx.h"
#include "BattlegroundScene.h"


int BattlegroundScene::render(sf::RenderWindow & window, Save& save, sf::View& view)
{
	if (save.isLoadingMode()) loadGameAction(save);
	else setUpNewMap(save); //making map NxN
	selectingMode = save.isSelectingMode();

	while (selectingMode) { //loop for placing units on map
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
		if (menuOpened) {
			exit.setPosition(view.getCenter().x - 75, view.getCenter().y - 50);
			savegame.setPosition(view.getCenter().x - 75, view.getCenter().y + 50);
			window.draw(exit);
			window.draw(savegame);
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
			mapClickedPosition(window, view, clickedPosX);
			if (menuOpened) {
				if (exit.isMouseOver(mouse, window, view)) return 5;
				if (savegame.isMouseOver(mouse, window, view)) {
					//saveGameAction(save);
					menuOpened = false;
					nullSquare = true;
				}
			}
			if (!nullSquare) {
				selectingMouseClicked(save);
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
				menuOpened = !menuOpened;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			mouseHold = false;
			holding = false;
		}
		window.display();
	}

	//Start of playing mode
	text1.setString("Tura gracza A");
	selectedUnit.setTexture(knightImA);
	unitType = KnightA;
	//if (knightsA.size() == 0) changeUnitTurn(unitType);
	changeUnitTurn(unitType);

	while (1) {
		window.clear(sf::Color::Black);
		window.pollEvent(event);
		temp = first;
		// DRAWING OBJECTS
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
		if (menuOpened) {
			exit.setPosition(view.getCenter().x - 75, view.getCenter().y - 50);
			savegame.setPosition(view.getCenter().x - 75, view.getCenter().y + 50);
			window.draw(exit);
			window.draw(savegame);
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
		// EVENTS
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
				menuOpened = true;
			}
		}
		if ((mouse.isButtonPressed(sf::Mouse::Left)) && (mouseHold != true)) {
			if (menuOpened) {
				if (exit.isMouseOver(mouse, window, view)) return 5;
				if (savegame.isMouseOver(mouse, window, view)) {
					saveGameAction(save);
					menuOpened = false;
					nullSquare = true;
				}
			}
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
		teamASelecting = true;
		break;
	}
}

void BattlegroundScene::placeAnotherUnit()
{
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
			if (!knightsA.at(i)->hadTurn()) {
				std::cout << "POINK" << std::endl;
				return;
			}
		}
		std::cout << "1! " << std::endl;
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
		std::cout << "2! " << std::endl;
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
		std::cout << "3! " << std::endl;
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
		std::cout << "4! " << std::endl;
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
		std::cout << "5! " << std::endl;
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
		std::cout << "6! " << std::endl;
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
		std::cout << "7! " << std::endl;
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
		std::cout << "8! " << std::endl;
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
		std::cout << "9! " << std::endl;
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
		std::cout << "10! " << std::endl;
		type = KnightA;
		text1.setString("Tura gracza A");
		selectedUnit.setTexture(knightImA);
		setNewTurn();
		changeUnitTurn(unitType);
	}
}

void BattlegroundScene::setUpNewMap(Save & save)
{
	for (unsigned int i = 0; i < save.getMapSize(); i++) {
		for (unsigned int j = 0; j < save.getMapSize(); j++) {
			std::cout << "x: " << i << "y: " << j << std::endl;
			if ((i == 0) && (j == 0)) {
				first = new Square;
				first->setTexture(mapTile);
				first->setPosition(0, 0);
			}
			else if ((i == 0) && (j == 1)) {
				prev = new Square;
				prev->setTexture(mapTile);
				prev->setPosition(64, 0);
				first->setRight(prev);
				prev->setLeft(first);
			}
			else if ((i == 0) && (j > 1)) {
				temp = new Square;
				temp->setTexture(mapTile);
				temp->setPosition((float)j * 64, 0);
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
	if (save.isSelectingMode()) {
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
	}
	temp = nullptr;
	prev = nullptr;
	changeUnitSelect(unitType);
}

void BattlegroundScene::selectingMouseClicked(Save& save)
{
	if (actual == nullptr) {
		if (temp != nullptr) {
			if ((teamASelecting) && (clickedPosX > save.getMapSize() / 2)) {
			}
			else if ((!teamASelecting) && (clickedPosX <= (save.getMapSize() + 1) / 2)) {
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
			placeAnotherUnit();
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
					if ((teamASelecting) && (clickedPosX > save.getMapSize() / 2)) {}
					else if ((!teamASelecting) && (clickedPosX <= (save.getMapSize() + 1) / 2)) {}
					else {
						temp->touch();
						temp->setTexture(mapTileTouched);
					}
					actual->touch();
					actual->setTexture(mapTile);
					actual = temp;
				}
			}
		}
	}
}

void BattlegroundScene::saveGameAction(Save& save)
{
	Unit *tempUnit;
	ofstr.open("save.txt");
	if (!ofstr.good()) { return; }
	ofstr << "mps " << save.getMapSize() << std::endl;
	for (int i = 0; i < knightsA.size(); i++) {
		tempUnit = knightsA.at(i);
		ofstr << "kna ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < knightsB.size(); i++) {
		tempUnit = knightsB.at(i);
		ofstr << "knb ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < warriorsA.size(); i++) {
		tempUnit = warriorsA.at(i);
		ofstr << "waa ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < warriorsB.size(); i++) {
		tempUnit = warriorsB.at(i);
		ofstr << "wab ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < ridersA.size(); i++) {
		tempUnit = ridersA.at(i);
		ofstr << "ria ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < ridersB.size(); i++) {
		tempUnit = ridersB.at(i);
		ofstr << "rib ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < magesA.size(); i++) {
		tempUnit = magesA.at(i);
		ofstr << "maa ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < magesB.size(); i++) {
		tempUnit = magesB.at(i);
		ofstr << "mab ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < archersA.size(); i++) {
		tempUnit = archersA.at(i);
		ofstr << "ara ";
		writeDownUnit(ofstr, tempUnit);
	}
	for (int i = 0; i < archersB.size(); i++) {
		tempUnit = archersB.at(i);
		ofstr << "arb ";
		writeDownUnit(ofstr, tempUnit);
	}
	ofstr.close();
}

void BattlegroundScene::writeDownUnit(std::ofstream & ofstr, Unit *tempUnit)
{
	ofstr << (tempUnit->getPosition().x / 64) << " " << (tempUnit->getPosition().y / 64) << " " << tempUnit->getHp() << " " << tempUnit->getTempMovement() << " ";
	if (tempUnit->canAttack()) ofstr << "can ";
	else ofstr << "not ";
	if (tempUnit->hadTurn()) ofstr << "yes ";
	else ofstr << "no ";
	if (tempUnit->isMovable()) ofstr << "yes ";
	else ofstr << "no ";
	ofstr << std::endl;
}

void BattlegroundScene::loadGameAction(Save& save)
{
	std::ifstream ifstr;
	ifstr.open("save.txt");
	std::string info;
	unsigned int tempInt;
	ifstr >> info;
	if (info == "mps") {
		ifstr >> tempInt;
		save.setMapSize(tempInt);
		setUpNewMap(save);
	}
	loadingUnits(ifstr);
}

void BattlegroundScene::loadingUnits(std::ifstream& ifstr)
{
	Unit *tempUnit;
	std::string info;
	while (ifstr.good()) {
		ifstr >> info;
		std::cout << info << " ";
		if (info == "kna") {
			tempUnit = new Knight(true, &knightsA);
			tempUnit->setType(0);
			knightsA.push_back(tempUnit);
			readUnit(ifstr, tempUnit, knightImA);
		}
		else if (info == "waa") {
			tempUnit = new Warrior(true, &warriorsA);
			tempUnit->setType(1);
			warriorsA.push_back(tempUnit);
			readUnit(ifstr, tempUnit, warriorImA);
		}
		else if (info == "ara") {
			tempUnit = new Archer(true, &archersA);
			tempUnit->setType(2);
			archersA.push_back(tempUnit);
			readUnit(ifstr, tempUnit, archerImA);
		}
		else if (info == "ria") {
			tempUnit = new Rider(true, &ridersA);
			tempUnit->setType(3);
			ridersA.push_back(tempUnit);
			readUnit(ifstr, tempUnit, riderImA);
		}
		else if (info == "maa") {
			tempUnit = new Mage(true, &magesA);
			tempUnit->setType(4);
			magesA.push_back(tempUnit);
			readUnit(ifstr, tempUnit, mageImA);
		}
		else if (info == "knb") {
			tempUnit = new Knight(false, &knightsB);
			tempUnit->setType(5);
			knightsB.push_back(tempUnit);
			readUnit(ifstr, tempUnit, knightImB);
		}
		else if (info == "wab") {
			tempUnit = new Warrior(false, &warriorsB);
			tempUnit->setType(6);
			warriorsB.push_back(tempUnit);
			readUnit(ifstr, tempUnit, warriorImB);
		}
		else if (info == "arb") {
			tempUnit = new Archer(false, &archersB);
			tempUnit->setType(7);
			archersB.push_back(tempUnit);
			readUnit(ifstr, tempUnit, archerImB);
		}
		else if (info == "rib") {
			tempUnit = new Rider(false, &ridersB);
			tempUnit->setType(8);
			ridersB.push_back(tempUnit);
			readUnit(ifstr, tempUnit, riderImB);
		}
		else if (info == "mab") {
			tempUnit = new Mage(false, &magesB);
			tempUnit->setType(9);
			magesB.push_back(tempUnit);
			readUnit(ifstr, tempUnit, mageImB);
		}
	}
}

void BattlegroundScene::readUnit(std::ifstream & ifstr, Unit * tempUnit, sf::Texture& texture)
{
	Square *tempSquare;
	std::string info;
	int tempInt;
	double tempDouble;
	ifstr >> x >> y;
	std::cout << x << " " << y << " ";
	tempSquare = locateSquare(x, y);
	tempSquare->putUnit(tempUnit);
	ifstr >> tempDouble;
	tempUnit->setHp(tempDouble);
	ifstr >> tempInt;
	tempUnit->setTempMovement(tempInt);
	ifstr >> info;
	setUpUnit(tempSquare, texture);
	std::cout << tempDouble << " " << tempInt << " " << info << " ";
	if (info == "can") tempUnit->setAttackAbility(true);
	else if (info == "not") tempUnit->setAttackAbility(false);
	ifstr >> info;
	std::cout << info << " ";
	if (info == "yes") tempUnit->setTurn(true);
	else if (info == "no") tempUnit->setTurn(false);
	ifstr >> info;
	std::cout << info << std::endl;
	if (info == "yes") tempUnit->setMovable(true);
	else if (info == "no") tempUnit->setMovable(false);
}

void BattlegroundScene::mapClickedPosition(sf::RenderWindow & window, sf::View& view)
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
}

void BattlegroundScene::mapClickedPosition(sf::RenderWindow & window, sf::View & view, int& ClickedPosX)
{
	clickedPosX = 1;
	for (int i = 0; i < (int)((mouse.getPosition(window).x + view.getCenter().x - 512) / 64); i++) {
		if (temp->getRight() == nullptr) {
			nullSquare = true;
			break;
		}
		clickedPosX = clickedPosX + 1;
		temp = temp->getRight();
	}
	for (int i = 0; i < (int)((mouse.getPosition(window).y + view.getCenter().y - 400) / 64); i++) {
		if ((temp->getDown() == nullptr) || (nullSquare)) {
			nullSquare = true;
			break;
		}
		temp = temp->getDown();
	}
}

Square * BattlegroundScene::locateSquare(int x, int y)
{
	Square *tempSquare = first;
	nullSquare = false;
	for (int i = 0; i < x; i++) {
		if (tempSquare->getRight() == nullptr) {
			nullSquare = true;
			break;
		}
		tempSquare = tempSquare->getRight();
	}
	for (int i = 0; i < y; i++) {
		if ((tempSquare->getDown() == nullptr) || (nullSquare)) {
			nullSquare = true;
			break;
		}
		tempSquare = tempSquare->getDown();
	}
	if (nullSquare) return nullptr;
	else return tempSquare;
}

void BattlegroundScene::setUpUnit(Square *temp, sf::Texture & texture)
{
	temp->getUnit()->setTexture(texture);
	temp->getUnit()->setPosition(temp->getPosition());
	temp->getUnit()->setScale(0.5, 0.5);
	temp->getUnit()->setHPBar(new sf::Sprite); //something is not yes
	temp->getUnit()->setHPBarTexture(hpbarIm);
	temp->getUnit()->getHPBar()->setScale(temp->getUnit()->getHp() / temp->getUnit()->getMaxHp(), 0.4);
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
	for (int i = 0; i < ridersA.size(); i++) {
		ridersA.at(i)->prepareForTurn();
	}
	for (int i = 0; i < ridersB.size(); i++) {
		ridersB.at(i)->prepareForTurn();
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
			std::cout << actual->getUnit()->getAttackRange();
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
	savegameIm.loadFromFile("include/buttons/savegame.png");
	exitIm.loadFromFile("include/buttons/exit2.png");
	move.setTexture(moveIm);
	idle.setTexture(idleIm);
	fight.setTexture(fightIm);
	savegame.setTexture(savegameIm);
	exit.setTexture(exitIm);

}


BattlegroundScene::~BattlegroundScene()
{
}
