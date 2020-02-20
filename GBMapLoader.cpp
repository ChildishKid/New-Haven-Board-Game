#include <fstream>
#include "GBMapLoader.h"

void GBMapLoader::save(GBMaps* gameBoard, string fileName) {
	ofstream output(fileName);

	output << gameBoard->getNumberOfPlayers() << endl;

	gameBoard->iterate = gameBoard->begin();

	for (; gameBoard->iterate != gameBoard->end(); ++gameBoard->iterate) {
		output << gameBoard->iterate->second->getX() << endl;
		output << gameBoard->iterate->second->getY() << endl;
		output << gameBoard->iterate->second->getStatus() << endl;
		output << gameBoard->iterate->second->getTopLeft()->getType() << endl;
		output << gameBoard->iterate->second->getTopRight()->getType() << endl;
		output << gameBoard->iterate->second->getBottomLeft()->getType() << endl;
		output << gameBoard->iterate->second->getBottomRight()->getType() << endl;
	}

	output.close();
}

GBMaps* GBMapLoader::load(string fileName) {

	try {
		ifstream inputStream(fileName);

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

			Type resourceTL;
			inputStream >> resourceTL;
			Type resourceTR;
			inputStream >> resourceTR;
			Type resourceBL;
			inputStream >> resourceBL;
			Type resourceBR;
			inputStream >> resourceBR;

			square->getTopLeft()->setType(new Type(resourceTL));
			square->getTopRight()->setType(new Type(resourceTR));
			square->getBottomLeft()->setType(new Type(resourceBL));
			square->getBottomRight()->setType(new Type(resourceBR));
		}

		inputStream.close();
		return gameBoard;
	}
	catch (exception e) {
		cout << "Invalid Save File!" << endl;
		return NULL;
	}
}