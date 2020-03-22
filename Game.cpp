#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <map>
#include "Game.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
using namespace std;

Game::Game() {
	setupGBMap();
	cout << "Creating a deck with 144 building tiles and 60 harvest tiles..." << endl;
	deck = new Deck();
	initializeBuildingPool();
	createPlayers();
	initializeResources();
	sort(players->begin(), players->end(), Player::sortById);
};

void Game::setupGBMap() {
	int numOfPlayers;
	cout << "Please enter the number of players (2-4): ";

	while (!(cin >> numOfPlayers) || numOfPlayers < 2 || numOfPlayers > 4) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a number between 2 and 4: ";
	}

	cout << "Setting up the correct GBMap..." << endl;
	if (numOfPlayers == 2) {
		Game::gbMap = GBMapLoader::load("TwoPlayersGBMap.txt");
	}
	else  if (numOfPlayers == 3) {
		Game::gbMap = GBMapLoader::load("ThreePlayersGBMap.txt");
	}
	else {
		Game::gbMap = GBMapLoader::load("FourPlayersGBMap.txt");
	}
};

void Game::createPlayers() {
	string name;
	int id;
	players = new vector<Player*>();
	for (int i = 0; i < gbMap->getNumberOfPlayers(); i++) {
		cout << "Please enter the name of player " << i + 1 << ": ";
		cin >> name;
		cout << "Please enter the ID of player " << i + 1 << ": ";
		cin >> id;
		Player* player = new Player(name, id, gbMap);

		cout << "Creating " << name << "'s empty hand..." << endl;
		Hand* hand = new Hand();
		hand->setDeck(deck);
		player->setPlayersHand(hand);

		cout << "Setting " << name << "'s VGMap..." << endl;
		player->setPlayersVGMap(VGMapLoader::load("VGMap.txt"));

		cout << "Drawing " << name << "'s 6 buildings..." << endl;
		for (int j = 0; j < 6; j++) {
			player->drawBuilding();
		}

		cout << "Drawing " << name << "'s 2 harvest tiles..." << endl;
		for (int j = 0; j < 2; j++) {
			player->drawHarvestTile();
		}

		cout << "Drawing " << name << "'s shipment tile..." << endl;
		player->getPlayersHand()->setShipmentTile(
			static_cast<HarvestTile*>(deck->draw(ResourceType::HarvestTile)));

		players->insert(players->begin(), player);
	}
};

void Game::initializeBuildingPool() {
	cout << "Drawing 5 building tiles and placing them in the pool..." << endl;
	buildingPool = new vector<Building*>();
	for (int i = 0; i < 5; i++) {
		buildingPool->push_back(static_cast<Building*>(deck->draw(ResourceType::Building)));
	}
}

void Game::initializeResources() {
	cout << "Using resourceTracker to set game's resources markers..." << endl;
	map<string, int> resources = players->front()->resourceTracker();
	sheepResourceMarker = new int(resources["Sheep"]);
	stoneResourceMarker = new int(resources["Stone"]);
	timberResourceMarker = new int(resources["Timber"]);
	wheatResourceMarker = new int(resources["Wheat"]);
}

GBMaps* Game::getGbMap() const {
	return gbMap;
}

vector<Player*>* Game::getPlayers() const {
	return players;
}

vector<Building*>* Game::getBuildingPool() const {
	return buildingPool;
}

int Game::getSheepResourceMarker() const {
	return *sheepResourceMarker;
}

int Game::getStoneResourceMarker() const {
	return *stoneResourceMarker;
}

int Game::getTimberResourceMarker() const {
	return *timberResourceMarker;
}

int Game::getWheatResourceMarker() const {
	return *wheatResourceMarker;
}

void Game::setSheepResourceMarker(int s) {
	*sheepResourceMarker = s;
}

void Game::setStoneResourceMarker(int s) {
	*stoneResourceMarker = s;
}

void Game::setTimberResourceMarker(int s) {
	*timberResourceMarker = s;
}

void Game::setWheatResourceMarker(int s) {
	*wheatResourceMarker = s;
}

Deck* Game::getDeck() const {
	return deck;
}

void Game::displayGameBoard() const {
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

		// Create horizontal coordinate system
		string xcoordinates = "";
		for (int i = 0; i < gbMap->getWidth(); i++) {
			for (int j = 0; j < 7; j++)
				xcoordinates += " ";
			xcoordinates += to_string(i);
		}

		// Create vertical border lines and coordinate system, and display table to console
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

		// Create horizontal coordinate system
		string xcoordinates = "";
		for (int i = 0; i < gbMap->getWidth(); i++) {
			for (int j = 0; j < 7; j++)
				xcoordinates += " ";
			xcoordinates += to_string(i);
		}

		// Create vertical border lines and coordinate system, and display table to console
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
		<< "Stone (" + to_string(*stoneResourceMarker) + "), "
		<< "Timber (" + to_string(*timberResourceMarker) + "), "
		<< "Wheat (" + to_string(*wheatResourceMarker) + "), "
		<< "Sheep (" + to_string(*sheepResourceMarker) + ")"
		<< endl << endl;

	// Display Building Pool
	cout << "   BUILDING POOL: " << endl;

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

void Game::displayVillageBoard(Player* player) const {
	cout << endl << "====== " << *player->getName() << "'s VILLAGE BOARD ======" << endl;
	VGMap* vgMap = player->getVGMap();

	string topBotBorder = "   ";
	string inBetweenBorder = "   ";
	for (int i = 0; i < (vgMap->getWidth() * 8 + vgMap->getWidth() + 1); i++) {
		topBotBorder += "=";
		inBetweenBorder += "-";
	}

	// Create horizontal coordinate system
	string xcoordinates = "";
	for (int i = 0; i < vgMap->getWidth(); i++) {
		for (int j = 0; j < 8; j++)
			xcoordinates += " ";
		xcoordinates += to_string(i);
	}

	// Create vertical border lines and coordinate system, and display table to console
	cout << xcoordinates << endl;
	cout << topBotBorder << endl;
	for (int i = 0; i < vgMap->getHeight(); i++) {

		string row1 = " " + to_string(i) + " |";

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
				if (vgMap->getCircle(x, y)->getBuilding()->getActualCost() > 0)
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
}

void Game::displayPlayerHand(Player* player) const {
	cout << endl << "====== " << *player->getName() << "'s HAND ======" << endl;

	// Display Harvest Tiles in hand
	cout << endl << "   HARVEST TILES: " << endl;

	string topBotBorder = "   ";
	string inBetweenBorder = "   ";
	for (int i = 0; i < (player->getPlayersHand()->getHarvestTiles()->size() * 7 + player->getPlayersHand()->getHarvestTiles()->size() + 1); i++) {
		topBotBorder += "=";
		inBetweenBorder += "-";
	}

	// Create horizontal coordinate system
	string xcoordinates = "";
	for (int i = 0; i < player->getPlayersHand()->getHarvestTiles()->size(); i++) {
		for (int j = 0; j < 7; j++)
			xcoordinates += " ";
		xcoordinates += to_string(i);
	}

	// Create vertical border lines and coordinate system, and display table to console
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
	cout << endl << "   BUILDING POOL: " << endl;

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

pair<int,int> Game::pickHarvestTile(Player* player) {
	// Give option to see village board
	while (true) {
		try {
			system("CLS");
			displayGameBoard();
			displayPlayerHand(player);

			cout << "What would you like to do?" << endl;
			cout << "\t1- See Village Board." << endl;
			cout << "\t2- Place Harvest Tile." << endl;
			cout << "Option: ";

			int input;
			cin.clear();
			cin >> input;

			if (input != 1 && input != 2)
				throw 0;

			if (input == 1) {
				system("CLS");
				displayVillageBoard(player);
				displayPlayerHand(player);
				system("pause");
				continue;
			}

			break;
		}
		catch (int e) {
			continue;
		}
	}

	// Pick harvest tile
	system("CLS");
	displayGameBoard();
	displayPlayerHand(player);
	cout << "Which harvest tile would you like to pick?" << endl;
	int pick;
	while (true) {
		try {
			cout << "Option: ";

			cin.clear();
			cin >> pick;

			if (pick < 0 || pick >= player->getPlayersHand()->getHarvestTiles()->size())
				throw 0;

			break;
		}
		catch (int e) {
			system("CLS");
			displayGameBoard();
			displayPlayerHand(player);
			cout << "Error: Out of range or invalid input!" << endl;
			cout << "Which harvest tile would you like to pick?" << endl;
			continue;
		}
	}

	// Give option to rotate it
	system("CLS");
	displayGameBoard();
	displayPlayerHand(player);
	cout << "Would you like to rotate it clockwise?" << endl;
	while (true) {
		try {
			cout << "(Y/N): ";

			string input;
			cin.clear();
			cin >> input;

			if (input != "Y" && input != "N" && input != "y" && input != "n")
				throw 0;

			if (input == "Y" || input == "y") {
				player->getPlayersHand()->getHarvestTiles()->at(pick)->rotateTile();
				throw 1;
			}
			else
				break;
		}
		catch (int e) {
			system("CLS");
			displayGameBoard();
			displayPlayerHand(player);
			if (e == 0)
				cout << "Error: Invalid input!" << endl;
			cout << "Would you like to rotate it clockwise?" << endl;
			continue;
		}
	}

	// Decide location to put them in:
	system("CLS");
	displayGameBoard();
	displayPlayerHand(player);
	while (true) {
		try {
			// Decide on location to put it on
			int x, y;
			cout << "Where would you like to place it?" << endl;
			cout << "X = ";
			cin.clear();
			cin >> x;
			if (x < 0 || x >= gbMap->getWidth())
				throw 0;

			cout << "Y = ";
			cin.clear();
			cin >> y;
			if (y < 0 || y >= gbMap->getHeight())
				throw 0;

			if (gbMap->getNumberOfPlayers() == 4) {
				if ((x == 0 && y == 0)
					|| (x == 0 && y == gbMap->getWidth() - 1)
					|| (x == gbMap->getHeight() - 1 && y == 0)
					|| (x == gbMap->getHeight() - 1 && y == gbMap->getWidth() - 1)) {
					throw 1;
				}
			}

			if (gbMap->getSquare(x, y)->getStatus() == true)
				throw 1;
			
			GBMaps::Square* square = gbMap->getSquare(x, y);
			vector<HarvestTile*>::iterator it = player->getPlayersHand()->getHarvestTiles()->begin();
			for (int i = 0; i < pick; i++)
				it++;
			HarvestTile* tile = *it;

			player->placeHarvestTile(x, y, tile);

			player->getPlayersHand()->getHarvestTiles()->erase(it);
			return make_pair(x,y);

		}
		catch (int e) {
			system("CLS");
			displayGameBoard();
			displayPlayerHand(player);
			if (e == 0)
				cout << "Error: Out of range or invalid input!" << endl;
			else if (e == 1)
				cout << "Error: Tile cannot be placed at specified location!" << endl;
			continue;
		}
	}
}

void Game::calculateResources(Player* player, pair<int,int> p) {

	ResourceCounter rc = ResourceCounter(gbMap);
	map<Type, int*>* collectedResources = rc.calculateCollectedResources(p.first, p.second);
	sheepResourceMarker = (*collectedResources)[Type::Sheep];
	stoneResourceMarker = (*collectedResources)[Type::Stone];
	timberResourceMarker = (*collectedResources)[Type::Timber];
	wheatResourceMarker = (*collectedResources)[Type::Wheat];

	cout << "Number of Sheep: " << *sheepResourceMarker << endl;
	cout << "Number of Stone: " << *stoneResourceMarker << endl;
	cout << "Number of Timber: " << *timberResourceMarker << endl;
	cout << "Number of Wheat: " << *wheatResourceMarker << endl;

}

void Game::calculateScores() {
	cout << "===== Final Scores =====" << endl;

	vector<Player*>::iterator it = players->begin();

	for (it = players->begin(); it != players->end(); it++) {
		Player* player = (*it);
		Score* count = new Score(player->getVGMap());
		player->setPlayersScore(new int(count->calculateScore()));

		cout << player->getName() << "'s score: " << player->getScore() << endl;

		delete count;
	}
}

void Game::displayWinner() {
	vector<Player*>::iterator it = players->begin();
	
	Player* winner = NULL;
	vector<Player*> tie;

	for (it = players->begin(); it != players->end(); it++) {
		Player* player = (*it);
		if (winner == NULL) {
			winner = player;
			continue;
		}

		if (winner->getScore() < player->getScore()) {
			winner = player;
			continue;
		}

		if (winner->getScore() == player->getScore()) {
			if (winner->getVGMap()->getNumberOfEmptySlots() > player->getVGMap()->getNumberOfEmptySlots()) {
				winner = player;
				continue;
			}
			if (winner->getVGMap()->getNumberOfEmptySlots() == player->getVGMap()->getNumberOfEmptySlots()) {
				if (winner->getPlayersHand()->getBuildings()->size() > player->getPlayersHand()->getBuildings()->size()) {
					winner = player;
					continue;
				}
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
		if (tie.front()->getScore() == winner->getScore()) {
			cout << "The Winners are: " << endl;

			vector<Player*>::iterator tieIt = tie.begin();

			for (tieIt = tie.begin(); tieIt != tie.end(); tieIt++) {
				Player* winners = (*tieIt);
				cout << winners->getName() << endl;
			}
			
			cout << "Congratulations!" << endl;
		}
		else {
			cout << "The Winner is: " << winner->getName() << "! Congratulations!" << endl;
		}
	}
	else {
		cout << "The Winner is: " << winner->getName() << "! Congratulations!" << endl;
	}


}

string Game::typePrefix(Type type) const {
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

void Game::run() {

	vector<Player*>::iterator it = players->begin();

	while (gbMap->getNumberOfEmptySlots() > 1) {
		Player* player = (*it);

		// 1. Place Harvest Tile
		pair<int,int> p = pickHarvestTile(player);

		system("CLS");
		displayGameBoard();
		displayPlayerHand(player);
		system("pause");

		// 2. Calculate Gathered Resources

		calculateResources(player, p);
		system("pause");

		// 3. Place Building Tile(s)

		
		// 4. Rotation to Share

		// 5. Draw Building Tiles
		// Note: First one must be from Building Pool
		// Note: Amount to draw is equal to all resource markers that are 0

		// Place all resources markets to 0

		// Draw Harvest Tiles

		it++;

		if (it == players->end())
			it = players->begin();
	}

	// 6. Calculate Total Scores
	system("CLS");
	calculateScores();

	// 7. Determine Winner

	displayWinner();
	system("pause");



}