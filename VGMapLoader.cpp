#include <iostream>
#include <fstream>
#include "VGMapLoader.h"
#include <string>
#include <stdlib.h>

void VGMapLoader::save(VGMap* gameboard, string fileName) {
	ofstream output(fileName);

	output << gameboard->getPlayerName() << endl;
	output << gameboard->getPlayerID() << endl;

	for (int i = 0; i < gameboard->getWidth(); i++) {
		for (int j = 0; j < gameboard->getHeight(); j++) {
			output << gameboard->getCircle(i, j)->getCost() << endl;
			output << gameboard->getCircle(i, j)->getStatus() << endl;
			if (gameboard->getCircle(i, j)->getBuilding() == NULL) {
				output << "NULL" << endl;
			}
			else {
				output << *gameboard->getCircle(i, j)->getBuilding()->getCost() << endl;
				output << *gameboard->getCircle(i, j)->getBuilding()->getActualCost() << endl;
				output << *gameboard->getCircle(i, j)->getBuilding()->getType() << endl;
			}
		}
	}

}

VGMap* VGMapLoader::load(string fileName) {
	
	try {
		ifstream inputStream(fileName);
		string input;

		inputStream >> input;
		string playerName = input;

		inputStream >> input;
		int id = stoi(input);

		VGMap* gameboard = new VGMap(playerName, id);

		for (int i = 0; i < gameboard->getWidth(); i++) {
			for (int j = 0; j < gameboard->getHeight(); j++) {
				inputStream >> input;
				gameboard->getCircle(i, j)->setCost(stoi(input));

				inputStream >> input;
				bool status;
				if (stoi(input)) {
					status = true;
				}
				else {
					status = false;
				}
				gameboard->getCircle(i, j)->setStatus(status);

				inputStream >> input;

				if (input != "NULL") {
					string actualCost;
					inputStream >> actualCost;
					Type resource;
					inputStream >> resource;

					gameboard->getCircle(i, j)->setBuilding(new Building(new Type(resource), new int(stoi(input))));
					gameboard->getCircle(i, j)->getBuilding()->setActualCost(new int(stoi(actualCost)));
				}
			}
		}

		inputStream.close();
		return gameboard;
	}

	catch (exception e) {
		cout << "Invalid Save File! Exiting Program...";
		system("pause");
		exit(EXIT_FAILURE);
	}
}