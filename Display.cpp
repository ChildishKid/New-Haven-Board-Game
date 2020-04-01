#include "Display.h";

void Display::displayGameBoard(GBMaps* gbMap, map<Type, int>* resourceMarker) {
	cout << "====== GAME BOARD ======" << endl << endl;

	// Display for board of player size 2 and 3
	if (gbMap->getNumberOfPlayers() != 4) {

		// Create horizontal border lines for table
		string topBotBorder = "   ";
		string inBetweenBorder = "   ";
		for (int i = 0; i < (gbMap->getWidth() * 7 + gbMap->getWidth() + 1); i++) {
			topBotBorder += "=";
			inBetweenBorder += "-";
		}

		// Create horizontal coordinate std::system
		string xcoordinates = "";
		for (int i = 0; i < gbMap->getWidth(); i++) {
			for (int j = 0; j < 7; j++)
				xcoordinates += " ";
			xcoordinates += to_string(i);
		}

		// Create vertical border lines and coordinate std::system, and display table to console
		cout << topBotBorder << endl;
		for (int i = gbMap->getHeight() - 1; i >= 0; i--) {

			string row1 = " " + to_string(i) + " |";
			string row2 = "   |";
			for (int j = 0; j < gbMap->getWidth(); j++) {

				if (gbMap->getSquare(j, i)->getStatus() == 0) {
					row1 += "       |";
					row2 += "       |";
				}
				else {
					string tL = typePrefix(gbMap->getSquare(j, i)->getTopLeft()->getType());
					string tR = typePrefix(gbMap->getSquare(j, i)->getTopRight()->getType());
					string bL = typePrefix(gbMap->getSquare(j, i)->getBottomLeft()->getType());
					string bR = typePrefix(gbMap->getSquare(j, i)->getBottomRight()->getType());

					row1 += " " + tL + " " + tR + " |";
					row2 += " " + bL + " " + bR + " |";
				}
			}

			cout << row1 << endl;
			cout << row2 << endl;
			if (i != 0)
				cout << inBetweenBorder << endl;
		}
		cout << topBotBorder << endl;
		cout << xcoordinates << endl;
	}

	// Display for board of player size 4
	else {
		// Create horizontal border lines for table
		string topBotBorder = "           ";
		for (int i = 0; i < ((gbMap->getWidth() - 2) * 7 + gbMap->getWidth() - 1); i++) {
			topBotBorder += "=";
		}

		string inBetweenDashes = "   ";
		string secondAndBeforeLastBorder = "   ";
		int max = gbMap->getWidth() * 7 + gbMap->getWidth() + 1;
		for (int i = 0; i < max; i++) {
			if (i - 8 < 0 || i + 9 > max)
				secondAndBeforeLastBorder += "=";
			else
				secondAndBeforeLastBorder += "-";
			inBetweenDashes += "-";
		}

		// Create horizontal coordinate std::system
		string xcoordinates = "";
		for (int i = 0; i < gbMap->getWidth(); i++) {
			for (int j = 0; j < 7; j++)
				xcoordinates += " ";
			xcoordinates += to_string(i);
		}

		// Create vertical border lines and coordinate std::system, and display table to console
		cout << topBotBorder << endl;
		for (int i = gbMap->getHeight() - 1; i >= 0; i--) {

			string row1, row2;
			if (i == 0 || i == gbMap->getHeight() - 1) {
				row1 = " " + to_string(i) + "         |";
				row2 = "           |";
			}
			else {
				row1 = " " + to_string(i) + " |";
				row2 = "   |";
			}

			for (int j = 0; j < gbMap->getWidth(); j++) {

				if ((i == 0 && j == 0)
					|| (i == 0 && j == gbMap->getWidth() - 1)
					|| (i == gbMap->getHeight() - 1 && j == 0)
					|| (i == gbMap->getHeight() - 1 && j == gbMap->getWidth() - 1)) {
					continue;
				}

				if (gbMap->getSquare(j, i)->getStatus() == 0) {
					row1 += "       |";
					row2 += "       |";
				}
				else {
					string tL = typePrefix(gbMap->getSquare(j, i)->getTopLeft()->getType());
					string tR = typePrefix(gbMap->getSquare(j, i)->getTopRight()->getType());
					string bL = typePrefix(gbMap->getSquare(j, i)->getBottomLeft()->getType());
					string bR = typePrefix(gbMap->getSquare(j, i)->getBottomRight()->getType());

					row1 += " " + tL + " " + tR + " |";
					row2 += " " + bL + " " + bR + " |";
				}
			}

			cout << row1 << endl;
			cout << row2 << endl;

			if (i == 1 || i == gbMap->getHeight() - 1)
				cout << secondAndBeforeLastBorder << endl;
			else if (i != 0)
				cout << inBetweenDashes << endl;
		}
		cout << topBotBorder << endl;
		cout << xcoordinates << endl;
	}

	// Display Resource Track
	cout << endl << "   RESOURCE MARKERS: "
		<< "Stone (" + to_string((*resourceMarker)[Type::Stone]) + "), "
		<< "Timber (" + to_string((*resourceMarker)[Type::Timber]) + "), "
		<< "Wheat (" + to_string((*resourceMarker)[Type::Wheat]) + "), "
		<< "Sheep (" + to_string((*resourceMarker)[Type::Sheep]) + ")"
		<< endl << endl;
}

void Display::displayBuidlingPool(vector<Building*>* buildingPool) {
	// Display Building Pool
	cout << "   SHARED BUILDING POOL: " << endl;

	string topBotBorder = "   ";
	for (int i = 0; i < (buildingPool->size() * 6 + buildingPool->size() + 1); i++) {
		topBotBorder += "=";
	}

	string xcoordinates = "";
	for (int i = 0; i < buildingPool->size(); i++) {
		for (int j = 0; j < 6; j++)
			xcoordinates += " ";
		xcoordinates += to_string(i);
	}

	cout << xcoordinates << endl;
	cout << topBotBorder << endl;
	string row;
	for (int i = 0; i < buildingPool->size(); i++) {

		row = "   |";
		for (std::vector<Building*>::iterator it = buildingPool->begin(); it != buildingPool->end(); ++it) {
			row += " " + to_string(*(*it)->getCost()) + " " + typePrefix(*(*it)->getType()) + " |";
		}
	}
	cout << row << endl;
	cout << topBotBorder << endl;
}

void Display::displayVillageBoard(Player* player) {
	cout << endl << "====== " << *player->getName() << "'s VILLAGE BOARD ======" << endl;
	VGMap* vgMap = player->getVGMap();

	string topBotBorder = "   ";
	string inBetweenBorder = "   ";
	for (int i = 0; i < (vgMap->getWidth() * 8 + vgMap->getWidth() + 1); i++) {
		topBotBorder += "=";
		inBetweenBorder += "-";
	}

	// Create horizontal coordinate std::system
	string xcoordinates = "";
	for (int i = 0; i < vgMap->getWidth(); i++) {
		for (int j = 0; j < 8; j++)
			xcoordinates += " ";
		xcoordinates += to_string(i);
	}

	// Create vertical border lines and coordinate std::system, and display table to console
	cout << topBotBorder << endl;
	for (int i = 0; i < vgMap->getHeight(); i++) {

		string row1 = " " + to_string(vgMap->getHeight() - 1 - i) + " |";

		for (int j = 0; j < vgMap->getWidth(); j++) {

			int x = j;
			int y = vgMap->getHeight() - 1 - i;

			if (vgMap->getCircle(x, y)->getStatus() == 0) {
				string cost = to_string(vgMap->getCircle(x, y)->getCost());
				row1 += " " + cost + "      |";
			}
			else {
				string cost, flip, resource;

				// if actual cost is greater than 0, this means the building was flipped
				if (*vgMap->getCircle(x, y)->getBuilding()->getActualCost() != 0)
					flip = "D";
				else
					flip = "U";

				cost = to_string(vgMap->getCircle(x, y)->getCost());
				resource = typePrefix(*vgMap->getCircle(x, y)->getBuilding()->getType());

				row1 += " " + cost + " " + resource + " " + flip + " |";
			}
		}

		cout << row1 << endl;

		if (i != vgMap->getHeight() - 1)
			cout << inBetweenBorder << endl;
	}
	cout << topBotBorder << endl;
	cout << xcoordinates << endl;
	cout << endl;
}

void Display::displayPlayerHand(Player* player) {
	cout << endl << "====== " << *player->getName() << "'s HAND ======" << endl;

	// Display Harvest Tiles in hand

	if (player->getPlayersHand()->getShipmentTile() != NULL)
		cout << endl << "   HARVEST TILES: (+SHIPMENT TILE)" << endl;
	else
		cout << endl << "   HARVEST TILES: " << endl;

	string topBotBorder = "   ";
	string inBetweenBorder = "   ";
	for (int i = 0; i < (player->getPlayersHand()->getHarvestTiles()->size() * 7 + player->getPlayersHand()->getHarvestTiles()->size() + 1); i++) {
		topBotBorder += "=";
		inBetweenBorder += "-";
	}

	// Create horizontal coordinate std::system
	string xcoordinates = "";
	for (int i = 0; i < player->getPlayersHand()->getHarvestTiles()->size(); i++) {
		for (int j = 0; j < 7; j++)
			xcoordinates += " ";
		xcoordinates += to_string(i);
	}

	// Create vertical border lines and coordinate std::system, and display table to console
	cout << xcoordinates << endl;
	cout << topBotBorder << endl;

	string row1 = "   |";
	string row2 = "   |";

	for (std::vector<HarvestTile*>::iterator it = player->getPlayersHand()->getHarvestTiles()->begin();
		it != player->getPlayersHand()->getHarvestTiles()->end();
		++it) {
		string tL = typePrefix(*(*it)->getTopLeftNode());
		string tR = typePrefix(*(*it)->getTopRightNode());
		string bL = typePrefix(*(*it)->getBottomLeftNode());
		string bR = typePrefix(*(*it)->getBottomRightNode());

		row1 += " " + tL + " " + tR + " |";
		row2 += " " + bL + " " + bR + " |";
	}

	cout << row1 << endl;
	cout << row2 << endl;
	cout << topBotBorder << endl;

	// Display Building Tiles in hand
	cout << endl << "   PERSONAL BUILDING POOL: " << endl;

	topBotBorder = "   ";
	for (int i = 0; i < (player->getPlayersHand()->getBuildings()->size() * 6 + player->getPlayersHand()->getBuildings()->size() + 1); i++) {
		topBotBorder += "=";
	}

	xcoordinates = "";
	for (int i = 0; i < player->getPlayersHand()->getBuildings()->size(); i++) {
		for (int j = 0; j < 6; j++)
			xcoordinates += " ";
		xcoordinates += to_string(i);
	}

	cout << xcoordinates << endl;
	cout << topBotBorder << endl;
	string row;
	for (int i = 0; i < player->getPlayersHand()->getBuildings()->size(); i++) {

		row = "   |";
		for (std::vector<Building*>::iterator it = player->getPlayersHand()->getBuildings()->begin();
			it != player->getPlayersHand()->getBuildings()->end();
			++it) {
			row += " " + to_string(*(*it)->getCost()) + " " + typePrefix(*(*it)->getType()) + " |";
		}
	}
	cout << row << endl;
	cout << topBotBorder << endl << endl;
}

void Display::displayWinner(vector<Player*>* players) {
	vector<Player*>::iterator it = players->begin();

	Player* winner = NULL;
	vector<Player*> tie;

	cout << " " << endl;

	for (it = players->begin(); it != players->end(); it++) {
		Player* player = (*it);

		//First time through the loop
		if (winner == NULL) {
			winner = player;
			continue;
		}

		//Compare if current iteration is higher than the winner
		if (*winner->getScore() < *player->getScore()) {
			winner = player;
			continue;
		}

		//if two players have the same score, go into tie breakers
		if (*winner->getScore() == *player->getScore()) {
			//Winner has less empty spaces on their VGMap
			if (winner->getVGMap()->getNumberOfEmptySlots() > player->getVGMap()->getNumberOfEmptySlots()) {
				winner = player;
				continue;
			}
			//Winner and player have same amount of empty slots
			if (winner->getVGMap()->getNumberOfEmptySlots() == player->getVGMap()->getNumberOfEmptySlots()) {
				//Check who has less buildings in their hand
				if (winner->getPlayersHand()->getBuildings()->size() > player->getPlayersHand()->getBuildings()->size()) {
					winner = player;
					continue;
				}
				//There is a tie
				if (winner->getPlayersHand()->getBuildings()->size() == player->getPlayersHand()->getBuildings()->size()) {
					if (tie.size() > 0) {
						tie.push_back(player);
						continue;
					}
					tie.push_back(winner);
					tie.push_back(player);
					winner = player;
					continue;
				}

			}

		}
	}

	if (tie.size() > 0) {
		if (*tie.front()->getScore() == *winner->getScore()) {
			cout << "The Winners are: " << endl;

			vector<Player*>::iterator tieIt = tie.begin();

			for (tieIt = tie.begin(); tieIt != tie.end(); tieIt++) {
				Player* winners = (*tieIt);
				cout << *winners->getName() << endl;
			}

			cout << "Congratulations!" << endl;
		}
		else {
			cout << "The Winner is: " << *winner->getName() << "! Congratulations!" << endl;
		}
	}
	else {
		cout << "The Winner is: " << *winner->getName() << "! Congratulations!" << endl;
	}
}

string Display::typePrefix(Type type) {
	if (type == Type::Wheat)
		return "Wh";
	else if (type == Type::Stone)
		return "St";
	else if (type == Type::Sheep)
		return "Sh";
	else if (type == Type::Timber)
		return "Ti";
	else
		return "No";
}