#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <map>
#include "Game.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Display.h"
using namespace std;

Game::Game() {
	setupGBMap();
	cout << "Creating a deck with 144 building tiles and 60 harvest tiles..." << endl;
	deck = new Deck();
	initializeBuildingPool();
	createPlayers();
	resourceMarker = new map<Type, int>();
	initializeResources();
	shipmentTile = new bool(false);
	sort(players->begin(), players->end(), Player::sortById);
	rc = new ResourceCounter(gbMap);
};

Game::~Game() {
	delete gbMap;
	delete deck;
	delete players;
	delete buildingPool;
	delete shipmentTile;
	delete resourceMarker;

	gbMap = NULL;
	deck = NULL;
	players = NULL;
	buildingPool = NULL;
	shipmentTile = NULL;
	resourceMarker = NULL;
}

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
		//gbMap = new GBMaps(2);
	}
	else  if (numOfPlayers == 3) {
		 Game::gbMap = GBMapLoader::load("ThreePlayersGBMap.txt");
		//gbMap = new GBMaps(3);
	}
	else {
		 Game::gbMap = GBMapLoader::load("FourPlayersGBMap.txt");
		//gbMap = new GBMaps(4);
	}
};

void Game::createPlayers() {
	villageBuildingCount = new map<string, int>();
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
		(*villageBuildingCount)[*player->getName()] = 0;
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
	resourceMarker->insert({ Type::Sheep, 0 });
	resourceMarker->insert({ Type::Stone, 0 });
	resourceMarker->insert({ Type::Timber, 0 });
	resourceMarker->insert({ Type::Wheat, 0 });

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

Deck* Game::getDeck() const {
	return deck;
}

pair<int, int> Game::pickHarvestTile(Player* player) {

	// Pick harvest tile
	// std::system("CLS");
	Display::displayGameBoard(gbMap, resourceMarker);
	Display::displayBuidlingPool(buildingPool);
	Display::displayPlayerHand(player);
	Display::displayVillageBoard(player);

	int pick;
	while (true) {
		try {
			if (player->getPlayersHand()->getShipmentTile() != NULL)
				cout << "Which harvest tile would you like to pick? (Enter 99 to use Shipment Tile)" << endl;
			else
				cout << "Which harvest tile would you like to pick?" << endl;
			cout << "Option: ";

			cin.clear();
			cin >> pick;


			if (cin.fail() || pick < 0 || (pick >= player->getPlayersHand()->getHarvestTiles()->size() && pick != 99)
				|| (player->getPlayersHand()->getShipmentTile() == NULL && pick == 99))
				throw 0;

			break;
		}
		catch (int e) {
			// std::system("CLS");
			Display::displayGameBoard(gbMap, resourceMarker);
			Display::displayBuidlingPool(buildingPool);
			Display::displayPlayerHand(player);
			Display::displayVillageBoard(player);
			cout << "Error: Out of range or invalid input!" << endl;
			continue;
		}
	}

	if (pick != 99) {
		// Give option to rotate it
		// std::system("CLS");
		Display::displayGameBoard(gbMap, resourceMarker);
		Display::displayBuidlingPool(buildingPool);
		Display::displayPlayerHand(player);
		Display::displayVillageBoard(player);
		cout << "Would you like to rotate it clockwise?" << endl;
		while (true) {
			try {
				cout << "(Y/N): ";

				string input;
				cin.clear();
				cin >> input;

				if (cin.fail() || input != "Y" && input != "N" && input != "y" && input != "n")
					throw 0;

				if (input == "Y" || input == "y") {
					player->getPlayersHand()->getHarvestTiles()->at(pick)->rotateTile();
					throw 1;
				}
				else
					break;
			}
			catch (int e) {
				// std::system("CLS");
				Display::displayGameBoard(gbMap, resourceMarker);
				Display::displayBuidlingPool(buildingPool);
				Display::displayPlayerHand(player);
				Display::displayVillageBoard(player);
				if (e == 0)
					cout << "Error: Invalid input!" << endl;
				cout << "Would you like to rotate it clockwise?" << endl;
				continue;
			}
		}

		// Decide location to put them in:
		// std::system("CLS");
		Display::displayGameBoard(gbMap, resourceMarker);
		Display::displayBuidlingPool(buildingPool);
		Display::displayPlayerHand(player);
		Display::displayVillageBoard(player);
		while (true) {
			try {
				// Decide on location to put it on
				int x, y;
				cout << "Where would you like to place it?" << endl;
				cout << "X = ";
				cin.clear();
				cin >> x;
				if (cin.fail() || x < 0 || x >= gbMap->getWidth())
					throw 0;

				cout << "Y = ";
				cin.clear();
				cin >> y;
				if (cin.fail() || y < 0 || y >= gbMap->getHeight())
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
				return make_pair(x, y);

			}
			catch (int e) {
				// std::system("CLS");
				Display::displayGameBoard(gbMap, resourceMarker);
				Display::displayBuidlingPool(buildingPool);
				Display::displayPlayerHand(player);
				Display::displayVillageBoard(player);
				if (e == 0)
					cout << "Error: Out of range or invalid input!" << endl;
				else if (e == 1)
					cout << "Error: Tile cannot be placed at specified location!" << endl;
				continue;
			}
		}
	}
	else {
		// Choose types:
		Type* type;

		// std::system("CLS");
		Display::displayGameBoard(gbMap, resourceMarker);
		Display::displayBuidlingPool(buildingPool);
		Display::displayPlayerHand(player);
		Display::displayVillageBoard(player);
		while (true) {
			try {
				cout << "Pick Resource: (Sheep/Stone/Timber/Wheat)" << endl;
				cout << "Option: ";

				string input;
				cin.clear();
				cin >> input;

				if (cin.fail() || (input != "Sheep" && input != "Stone" && input != "Timber" && input != "Wheat"))
					throw 0;

				if (input == "Sheep")
					type = new Type(Type::Sheep);
				else if (input == "Stone")
					type = new Type(Type::Stone);
				else if (input == "Timber")
					type = new Type(Type::Timber);
				else
					type = new Type(Type::Wheat);

				break;
			}
			catch (int e) {
				// std::system("CLS");
				Display::displayGameBoard(gbMap, resourceMarker);
				Display::displayBuidlingPool(buildingPool);
				Display::displayPlayerHand(player);
				Display::displayVillageBoard(player);
				if (e == 0)
					cout << "Error: Invalid input!" << endl;
				continue;
			}
		}

		// Decide location to put them in:
		// std::system("CLS");
		Display::displayGameBoard(gbMap, resourceMarker);
		Display::displayBuidlingPool(buildingPool);
		Display::displayPlayerHand(player);
		Display::displayVillageBoard(player);
		while (true) {
			try {
				// Decide on location to put it on
				int x, y;
				cout << "Where would you like to place it?" << endl;
				cout << "X = ";
				cin.clear();
				cin >> x;
				if (cin.fail() || x < 0 || x >= gbMap->getWidth())
					throw 0;

				cout << "Y = ";
				cin.clear();
				cin >> y;
				if (cin.fail() || y < 0 || y >= gbMap->getHeight())
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

				player->placeHarvestTile(x, y, new HarvestTile(type, type, type, type));
				*shipmentTile = true;
				return make_pair(x, y);

			}
			catch (int e) {
				// std::system("CLS");
				Display::displayGameBoard(gbMap, resourceMarker);
				Display::displayBuidlingPool(buildingPool);
				Display::displayPlayerHand(player);
				Display::displayVillageBoard(player);
				if (e == 0)
					cout << "Error: Out of range or invalid input!" << endl;
				else if (e == 1)
					cout << "Error: Tile cannot be placed at specified location!" << endl;
				continue;
			}
		}
	}
}

bool Game::pickBuildingTile(Player* player) {

	// Determine if enough resources to build anything
	// std::system("CLS");
	Display::displayGameBoard(gbMap, resourceMarker);
	Display::displayBuidlingPool(buildingPool);
	Display::displayPlayerHand(player);
	Display::displayVillageBoard(player);

loop:
	while (true) {
		try {
			cout << "Would you like to build a Building?" << endl;
			cout << "(Y/N): ";

			string input;
			cin.clear();
			cin >> input;

			if (cin.fail() || input != "Y" && input != "N" && input != "y" && input != "n")
				throw 0;

			if (input == "Y" || input == "y") {

				// Choose which building to place
				// std::system("CLS");
				Display::displayGameBoard(gbMap, resourceMarker);
				Display::displayBuidlingPool(buildingPool);
				Display::displayPlayerHand(player);
				Display::displayVillageBoard(player);

				int pick;
				cout << "Which building tile would you like to pick?" << endl;
				cout << "Option: ";

				cin.clear();
				cin >> pick;

				if (cin.fail() || pick < 0 || pick >= player->getPlayersHand()->getBuildings()->size())
					throw 0;

				// Decided whether face up or face down.
				// std::system("CLS");
				Display::displayGameBoard(gbMap, resourceMarker);
				Display::displayBuidlingPool(buildingPool);
				Display::displayPlayerHand(player);
				Display::displayVillageBoard(player);
				string option;
				cout << "Would you like to build it face-up or face-down?" << endl;
				cout << "(U/D): ";

				string input;
				cin.clear();
				cin >> input;

				if (cin.fail() || input != "U" && input != "u" && input != "D" && input != "d")
					throw 0;
				else if (input == "U" || input == "u")
					option = "Up";
				else
					option = "Down";

				// Choose location to put building tile onto
				// std::system("CLS");
				Display::displayGameBoard(gbMap, resourceMarker);
				Display::displayBuidlingPool(buildingPool);
				Display::displayPlayerHand(player);
				Display::displayVillageBoard(player);
				int x, y;
				cout << "Where would you like to place it?" << endl;
				cout << "X = ";
				cin.clear();
				cin >> x;
				if (cin.fail() || x < 0 || x >= player->getVGMap()->getWidth())
					throw 0;

				cout << "Y = ";
				cin.clear();
				cin >> y;
				if (cin.fail() || y < 0 || y >= player->getVGMap()->getHeight())
					throw 0;

				if (player->getVGMap()->getCircle(x, y)->getStatus() == true)
					throw 1;
				/*
				bool firstPlacement = player->hasBuilt->find(*(player->getPlayersHand()->getBuildings()->at(pick)->getType()))->second == false;

				if (!firstPlacement && player->getVGMap()->getCircle(x, y)->validateCircle(*((player->getPlayersHand()->getBuildings()->at(pick)->getType()))))
					throw 2;
				*/

				if (!player->getVGMap()->validateTypeAdjacency(x, y, *(player->getPlayersHand()->getBuildings()->at(pick)->getType()))) {
					throw 2;
				}

				// Try to place tile
				if (option == "Down") {
					int cost = player->getVGMap()->getCircle(x, y)->getCost();
					Type resourceType = *player->getPlayersHand()->getBuildings()->at(pick)->getType();
					int resourceAmount;
					resourceAmount = (*resourceMarker)[resourceType];
					if (resourceAmount <= 0 || cost > resourceAmount) {
						// std::system("CLS");
						Display::displayGameBoard(gbMap, resourceMarker);
						Display::displayBuidlingPool(buildingPool);
						Display::displayPlayerHand(player);
						Display::displayVillageBoard(player);
						throw 3;
					}
					else {
						player->buildVillage(x, y, cost, pick, option);
						(*villageBuildingCount)[*player->getName()] = (*villageBuildingCount)[*player->getName()] + 1;
						notify(*player->getName() + " has built a village building.");
						(*resourceMarker)[resourceType] -= cost;
						notify("Resource markers have been updated accordingly.");
						return true;
					}
				}
				else if (option == "Up") {
					int cost = player->getVGMap()->getCircle(x, y)->getCost();

					// Make sure that it can be placed at the right spot
					if (cost != *player->getPlayersHand()->getBuildings()->at(pick)->getCost()) {

						// std::system("CLS");
						Display::displayGameBoard(gbMap, resourceMarker);
						Display::displayBuidlingPool(buildingPool);
						Display::displayPlayerHand(player);
						Display::displayVillageBoard(player);
						throw 4;
					}

					Type resourceType = *player->getPlayersHand()->getBuildings()->at(pick)->getType();
					int resourceAmount;
					resourceAmount = (*resourceMarker)[resourceType];

					if (resourceAmount <= 0 || cost > resourceAmount) {
						// std::system("CLS");
						Display::displayGameBoard(gbMap, resourceMarker);
						Display::displayBuidlingPool(buildingPool);
						Display::displayPlayerHand(player);
						Display::displayVillageBoard(player);
						throw 3;
					}
					else {
						player->buildVillage(x, y, cost, pick, option);
						(*villageBuildingCount)[*player->getName()] = (*villageBuildingCount)[*player->getName()] + 1;
						notify(*player->getName() + " has built a village building.");
						(*resourceMarker)[resourceType] -= cost;
						notify("Resource markers have been updated accordingly.");
						return true;
					}
				}

			}
			else
				return false;
		}
		catch (int e) {
			// std::system("CLS");
			Display::displayGameBoard(gbMap, resourceMarker);
			Display::displayBuidlingPool(buildingPool);
			Display::displayPlayerHand(player);
			Display::displayVillageBoard(player);

			if (e == 0)
				cout << "Error: Out of range or invalid input!" << endl;
			else if (e == 1)
				cout << "Error: Tile cannot be placed at specified location! Already occupied..." << endl;
			else if (e == 2)
				cout << "Error: Tile cannot be placed at specified location! Must place adjancent to resource type..." << endl;
			else if (e == 3)
				cout << "Error: Tile cannot be placed at specified location! Not enough resources..." << endl;
			else if (e == 4)
				cout << "Error: Tile cannot be placed at specified location! Cost must be matching..." << endl;
			continue;
		}
	}



}

void Game::calculateResources(Player* player, pair<int, int> p) {

	map<Type, int*>* collectedResources = rc->calculateCollectedResources(p.first, p.second);
	(*resourceMarker)[Type::Sheep] = *(*collectedResources)[Type::Sheep];
	(*resourceMarker)[Type::Stone] = *(*collectedResources)[Type::Stone];
	(*resourceMarker)[Type::Timber] = *(*collectedResources)[Type::Timber];
	(*resourceMarker)[Type::Wheat] = *(*collectedResources)[Type::Wheat];
}

void Game::calculateScores() {
	cout << "===== Final Scores =====" << endl;

	for (int i = 0 ; i < players->size(); i++) {
		Score* count = new Score(players->at(i)->getVGMap());
		(players->at(i)->setPlayersScore(new int(count->calculateScore())));

		cout << *(players->at(i)->getName()) << "'s score: " << *(players->at(i)->getScore()) << endl;
	}
}

void Game::run() {

	vector<Player*>::iterator it = players->begin();

	while (gbMap->getNumberOfEmptySlots() > 1) {
		Player* player = (*it);
		currentPlayer = player;
		notify("It is now " + *player->getName() + "'s turn.");

		// 1. Place Harvest Tile and notify observers
		pair<int, int> harvestTile = pickHarvestTile(player);
		notify(*player->getName() + " has played a harvest tile.");

		// 2. Calculate Gathered Resources
		calculateResources(player, harvestTile);
		notify("The resources have been calculated.");

		// 3. Place Building
		// 4. Rotation to Share
		vector<Player*>::iterator sharing = it;
		int count = 0;
		while (count != players->size()) {
			if (!pickBuildingTile(*sharing)) {
				sharing++;
				if (sharing == players->end())
					sharing = players->begin();
				count++;
			}
		}


		// 5. Draw Building Tiles
		int draw_buildings = 0;
		if ((*resourceMarker)[Type::Wheat]== 0)
			draw_buildings++;
		if ((*resourceMarker)[Type::Stone] == 0)
			draw_buildings++;
		if ((*resourceMarker)[Type::Sheep] == 0)
			draw_buildings++;
		if ((*resourceMarker)[Type::Sheep] == 0)
			draw_buildings++;

		// Note: First one must be from Building Pool
		if (draw_buildings > 0) {

			// std::system("CLS");
			Display::displayGameBoard(gbMap, resourceMarker);
			Display::displayBuidlingPool(buildingPool);
			Display::displayPlayerHand(player);
			Display::displayVillageBoard(player);

			int input;
			while (true) {
				try {

					cout << "Choose one of the buildings from the SHARED BUILDING POOL" << endl;
					cout << "Option: ";

					cin.clear();
					cin >> input;

					if (cin.fail()) {
						throw 0;
					}

					if (input < 0 || input >= buildingPool->size())
						throw 1;

					break;
				}
				catch (int e) {
					// std::system("CLS");
					Display::displayGameBoard(gbMap, resourceMarker);
					Display::displayBuidlingPool(buildingPool);
					Display::displayPlayerHand(player);
					Display::displayVillageBoard(player);
					if (e == 0) {
						cout << "Error: Invalid input!" << endl;
					}
					else if (e == 1) {
						cout << "Error: Out of range!" << endl;
					}
					continue;
				}
			}

			player->getPlayersHand()->getBuildings()->push_back(getBuildingPool()->at(input));
			auto bpit = getBuildingPool()->begin();
			advance(bpit, input);
			getBuildingPool()->erase(bpit);
			draw_buildings--;
		}

		// Note: Amount to draw is equal to all resource markers that are 0
		while (draw_buildings > 0) {
			player->drawBuilding();
			draw_buildings--;
		}

		// Place all resources markets to 0
		(*resourceMarker)[Type::Sheep] = 0;
		(*resourceMarker)[Type::Stone] = 0;
		(*resourceMarker)[Type::Timber] = 0;
		(*resourceMarker)[Type::Wheat] = 0;

		// Draw Harvest Tiles
		player->drawHarvestTile();

		// Check to see if shipment tile has been used
		if (*shipmentTile) {
			*shipmentTile = false;
			gbMap->getSquare(harvestTile.first, harvestTile.second)->setBottomLeft(player->getPlayersHand()->getShipmentTile()->getBottomLeftNode());
			gbMap->getSquare(harvestTile.first, harvestTile.second)->setBottomRight(player->getPlayersHand()->getShipmentTile()->getBottomRightNode());
			gbMap->getSquare(harvestTile.first, harvestTile.second)->setTopLeft(player->getPlayersHand()->getShipmentTile()->getTopLeftNode());
			gbMap->getSquare(harvestTile.first, harvestTile.second)->setTopRight(player->getPlayersHand()->getShipmentTile()->getTopRightNode());
			player->getPlayersHand()->setShipmentTile(NULL);
		}
		
		// Replenish shared building pool
		while (buildingPool->size() != 5) {
			buildingPool->push_back(static_cast<Building*>(deck->draw(ResourceType::Building)));
		}

		//VGMap save function
		//VGMapLoader::save(player->getVGMap(), "VGMapTest.txt");

		it++;

		if (it == players->end())
			it = players->begin();
		
		notify(*player->getName() + " is at the end of his/her turn.");
	}

	// 6. Calculate Total Scores
	// std::system("CLS");
	calculateScores();

	// 7. Determine Winner
	Display::displayWinner(players);
	std::system("pause");
}
