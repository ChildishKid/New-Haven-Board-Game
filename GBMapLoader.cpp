#include <fstream>
#include "GBMapLoader.h"

void GBMapLoader::save(GBMaps* gameBoard) {
	ofstream output("BoardGameSave.txt");

	output << gameBoard->getNumberOfPlayers() << endl;

	gameBoard->iterate = gameBoard->begin();

	for (; gameBoard->iterate != gameBoard->end(); ++gameBoard->iterate) {
		output << gameBoard->iterate->second->getX() << endl;
		output << gameBoard->iterate->second->getY() << endl;
		output << gameBoard->iterate->second->getStatus() << endl;
		output << gameBoard->iterate->second->getTopLeft()->getTypeString() << endl;
		output << gameBoard->iterate->second->getTopRight()->getTypeString() << endl;
		output << gameBoard->iterate->second->getBottomLeft()->getTypeString() << endl;
		output << gameBoard->iterate->second->getBottomRight()->getTypeString() << endl;
	}

	output.close();
}

GBMaps* GBMapLoader::load() {

	try {
		ifstream inputStream("BoardGameSave.txt");

		// Load basic member variables
		string input;
		inputStream >> input;
		int numberOfPlayers = stoi(input);

		GBMaps* gameBoard = new GBMaps(numberOfPlayers);

		// Set up size depending on number of players
		int elements;
		if (gameBoard->getNumberOfPlayers() == 2) {
			elements = 25;
		}
		else if (gameBoard->getNumberOfPlayers() == 3) {
			elements = 35;
		}
		else {
			elements = 45;
		}

		// Load new square values onto map
		for (int i = 0; i < elements; i++) {
			inputStream >> input;
			int x = stoi(input);
			inputStream >> input;
			int y = stoi(input);
			GBMaps::Square* square = gameBoard->getSquare(x, y);

			inputStream >> input;
			bool status;
			if (stoi(input)) {
				status = true;
			}
			else {
				status = false;
			}
			square->setStatus(status);

			string resourceTL;
			inputStream >> resourceTL;
			string resourceTR;
			inputStream >> resourceTR;
			string resourceBL;
			inputStream >> resourceBL;
			string resourceBR;
			inputStream >> resourceBR;

			if (resourceTL == "Wheat") {
				square->setTopLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceTL == "Sheep") {
				square->setTopLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceTL == "Timber") {
				square->setTopLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceTL == "Stone") {
				square->setTopLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else {
				square->setTopLeft(GBMaps::Node(new Type(Type::None)));
			}

			if (resourceTR == "Wheat") {
				square->setTopRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceTR == "Sheep") {
				square->setTopRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceTR == "Timber") {
				square->setTopRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceTR == "Stone") {
				square->setTopRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else {
				square->setTopRight(GBMaps::Node(new Type(Type::None)));
			}

			if (resourceBL == "Wheat") {
				square->setBottomLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceBL == "Sheep") {
				square->setBottomLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceBL == "Timber") {
				square->setBottomLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceBL == "Stone") {
				square->setBottomLeft(GBMaps::Node(new Type(Type::Wheat)));
			}
			else {
				square->setBottomLeft(GBMaps::Node(new Type(Type::None)));
			}

			if (resourceBR == "Wheat") {
				square->setBottomRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceBR == "Sheep") {
				square->setBottomRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceBR == "Timber") {
				square->setBottomRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else if (resourceBR == "Stone") {
				square->setBottomRight(GBMaps::Node(new Type(Type::Wheat)));
			}
			else {
				square->setBottomRight(GBMaps::Node(new Type(Type::None)));
			}
		}

		inputStream.close();
		return gameBoard;
	}
	catch (exception e) {
		cout << "Invalid Save File!";
		return NULL;
	}
}