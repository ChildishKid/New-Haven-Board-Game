#include "GameObservers.h"
#include "Game.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

Observable::Observable() {
    observers = new vector<Observer*>();
}

Observable::~Observable() {
	delete observers;
	observers = NULL;
}

void Observable::attach(Observer* observer) {
    observers->push_back(observer);
};

void Observable::detach(Observer* observer) {
    for( std::vector<Observer*>::iterator iter = observers->begin(); iter != observers->end(); ++iter ) {
        if(*iter == observer) {
            observers->erase(iter);
            break;
        }
    }
}

void Observable::notify(Player* player, string message) {
    for( std::vector<Observer*>::iterator iter = observers->begin(); iter != observers->end(); ++iter ) {
        (*iter)->update(player, message);
    }
}

GameObserver::GameObserver() {
    subject = NULL;
}

GameObserver::GameObserver(Game* game) {
    subject = game;
    subject->attach(this);
};

GameObserver::~GameObserver() {
	subject->detach(this);
}

void GameObserver::update(Player* player, string message) {
	display();
}

void GameObserver::display() {
	cout << "====== GAME BOARD ======" << endl << endl;

	// Display for board of player size 2 and 3
	if (subject->getGbMap()->getNumberOfPlayers() != 4) {

		// Create horizontal border lines for table
		string topBotBorder = "   ";
		string inBetweenBorder = "   ";
		for (int i = 0; i < (subject->getGbMap()->getWidth() * 7 + subject->getGbMap()->getWidth() + 1); i++) {
			topBotBorder += "=";
			inBetweenBorder += "-";
		}

		// Create horizontal coordinate std::system
		string xcoordinates = "";
		for (int i = 0; i < subject->getGbMap()->getWidth(); i++) {
			for (int j = 0; j < 7; j++)
				xcoordinates += " ";
			xcoordinates += to_string(i);
		}

		// Create vertical border lines and coordinate std::system, and display table to console
		cout << topBotBorder << endl;
		for (int i = subject->getGbMap()->getHeight() - 1; i >= 0; i--) {

			string row1 = " " + to_string(i) + " |";
			string row2 = "   |";
			for (int j = 0; j < subject->getGbMap()->getWidth(); j++) {

				if (subject->getGbMap()->getSquare(j, i)->getStatus() == 0) {
					row1 += "       |";
					row2 += "       |";
				}
				else {
					string tL = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getTopLeft()->getType());
					string tR = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getTopRight()->getType());
					string bL = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getBottomLeft()->getType());
					string bR = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getBottomRight()->getType());

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
		for (int i = 0; i < ((subject->getGbMap()->getWidth() - 2) * 7 + subject->getGbMap()->getWidth() - 1); i++) {
			topBotBorder += "=";
		}

		string inBetweenDashes = "   ";
		string secondAndBeforeLastBorder = "   ";
		int max = subject->getGbMap()->getWidth() * 7 + subject->getGbMap()->getWidth() + 1;
		for (int i = 0; i < max; i++) {
			if (i - 8 < 0 || i + 9 > max)
				secondAndBeforeLastBorder += "=";
			else
				secondAndBeforeLastBorder += "-";
			inBetweenDashes += "-";
		}

		// Create horizontal coordinate std::system
		string xcoordinates = "";
		for (int i = 0; i < subject->getGbMap()->getWidth(); i++) {
			for (int j = 0; j < 7; j++)
				xcoordinates += " ";
			xcoordinates += to_string(i);
		}

		// Create vertical border lines and coordinate std::system, and display table to console
		cout << topBotBorder << endl;
		for (int i = subject->getGbMap()->getHeight() - 1; i >= 0; i--) {

			string row1, row2;
			if (i == 0 || i == subject->getGbMap()->getHeight() - 1) {
				row1 = " " + to_string(i) + "         |";
				row2 = "           |";
			}
			else {
				row1 = " " + to_string(i) + " |";
				row2 = "   |";
			}

			for (int j = 0; j < subject->getGbMap()->getWidth(); j++) {

				if ((i == 0 && j == 0)
					|| (i == 0 && j == subject->getGbMap()->getWidth() - 1)
					|| (i == subject->getGbMap()->getHeight() - 1 && j == 0)
					|| (i == subject->getGbMap()->getHeight() - 1 && j == subject->getGbMap()->getWidth() - 1)) {
					continue;
				}

				if (subject->getGbMap()->getSquare(j, i)->getStatus() == 0) {
					row1 += "       |";
					row2 += "       |";
				}
				else {
					string tL = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getTopLeft()->getType());
					string tR = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getTopRight()->getType());
					string bL = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getBottomLeft()->getType());
					string bR = Display::typePrefix(subject->getGbMap()->getSquare(j, i)->getBottomRight()->getType());

					row1 += " " + tL + " " + tR + " |";
					row2 += " " + bL + " " + bR + " |";
				}
			}

			cout << row1 << endl;
			cout << row2 << endl;

			if (i == 1 || i == subject->getGbMap()->getHeight() - 1)
				cout << secondAndBeforeLastBorder << endl;
			else if (i != 0)
				cout << inBetweenDashes << endl;
		}
		cout << topBotBorder << endl;
		cout << xcoordinates << endl;
	}

	// Display Resource Track
	cout << endl << "   RESOURCE MARKERS: "
		<< "Stone (" + to_string((*subject->getResourceMarker())[Type::Stone]) + "), "
		<< "Timber (" + to_string((*subject->getResourceMarker())[Type::Timber]) + "), "
		<< "Wheat (" + to_string((*subject->getResourceMarker())[Type::Wheat]) + "), "
		<< "Sheep (" + to_string((*subject->getResourceMarker())[Type::Sheep]) + ")"
		<< endl << endl;

	// Display Building Pool
	cout << "   SHARED BUILDING POOL: " << endl;

	string topBotBorder = "   ";
	for (int i = 0; i < (subject->getBuildingPool()->size() * 6 + subject->getBuildingPool()->size() + 1); i++) {
		topBotBorder += "=";
	}

	string xcoordinates = "";
	for (int i = 0; i < subject->getBuildingPool()->size(); i++) {
		for (int j = 0; j < 6; j++)
			xcoordinates += " ";
		xcoordinates += to_string(i);
	}

	cout << xcoordinates << endl;
	cout << topBotBorder << endl;
	string row;
	for (int i = 0; i < subject->getBuildingPool()->size(); i++) {

		row = "   |";
		for (std::vector<Building*>::iterator it = subject->getBuildingPool()->begin(); it != subject->getBuildingPool()->end(); ++it) {
			row += " " + to_string(*(*it)->getCost()) + " " + Display::typePrefix(*(*it)->getType()) + " |";
		}
	}
	cout << row << endl;
	cout << topBotBorder << endl;
}

TurnObserver::TurnObserver() {
    subject = NULL;
}

TurnObserver::TurnObserver(Game* game) {
    subject = game;
    subject->attach(this);
};

TurnObserver::~TurnObserver() {
    subject->detach(this);
}

void TurnObserver::update(Player* player, string message) {
	display(player, message);
}

void TurnObserver::display(Player* player, string message) {
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
				resource = Display::typePrefix(*vgMap->getCircle(x, y)->getBuilding()->getType());

				row1 += " " + cost + " " + resource + " " + flip + " |";
			}
		}

		cout << row1 << endl;

		if (i != vgMap->getHeight() - 1)
			cout << inBetweenBorder << endl;
	}
	cout << topBotBorder << endl;
	cout << xcoordinates << endl;

	cout << endl << "====== " << *player->getName() << "'s HAND ======" << endl;

	// Display Harvest Tiles in hand
	if (player->getPlayersHand()->getShipmentTile() != NULL)
		cout << endl << "   HARVEST TILES: (+SHIPMENT TILE)" << endl;
	else
		cout << endl << "   HARVEST TILES: " << endl;

	topBotBorder = "   ";
	inBetweenBorder = "   ";
	for (int i = 0; i < (player->getPlayersHand()->getHarvestTiles()->size() * 7 + player->getPlayersHand()->getHarvestTiles()->size() + 1); i++) {
		topBotBorder += "=";
		inBetweenBorder += "-";
	}

	// Create horizontal coordinate std::system
	xcoordinates = "";
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
		string tL = Display::typePrefix(*(*it)->getTopLeftNode());
		string tR = Display::typePrefix(*(*it)->getTopRightNode());
		string bL = Display::typePrefix(*(*it)->getBottomLeftNode());
		string bR = Display::typePrefix(*(*it)->getBottomRightNode());

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
			row += " " + to_string(*(*it)->getCost()) + " " + Display::typePrefix(*(*it)->getType()) + " |";
		}
	}
	cout << row << endl;
	cout << topBotBorder << endl << endl;

	if (message != "") {
		cout << message << endl;
	}
}

GameStatisticsObserver::GameStatisticsObserver() {
    subject = NULL;
}

GameStatisticsObserver::GameStatisticsObserver(Game* game) {
    subject = game;
    subject->attach(this);
};

GameStatisticsObserver::~GameStatisticsObserver() {
    subject->detach(this);
}

void GameStatisticsObserver::update(Player* player, string message) {
	display();
}

void GameStatisticsObserver::display() {
	cout << endl << "====== GAME STATISTICS ======" << endl << endl;

	for (int i = 0; i < subject->getPlayers()->size(); i++) {
		Score* count = new Score(subject->getPlayers()->at(i)->getVGMap());
		(subject->getPlayers()->at(i)->setPlayersScore(new int(count->calculateScore())));

		cout << "Player: " + *(subject->getPlayers()->at(i)->getName());
		cout << ", Buildings: " + to_string(30 - subject->getPlayers()->at(i)->getVGMap()->getNumberOfEmptySlots());
		cout << " and Score: " << *(subject->getPlayers()->at(i)->getScore()) << endl;
	}
	cout << endl;
}

Observer::Observer() {
};

Observer::~Observer() {
};