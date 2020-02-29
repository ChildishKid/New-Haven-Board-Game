#include <iostream>
#include <fstream>
#include "VGMapLoader.h"
#include <string>

void VGMapLoader::save(VGMap* gameboard, string fileName) {
	ofstream output(fileName);

	output << gameboard->getPlayerName() << endl;

	for (int i = 0; i < gameboard->getWidth(); i++) {
		for (int j = 0; j < gameboard->getHeight(); j++) {
			output << gameboard->getCircle(i, j)->getCost() << endl;
			output << gameboard->getCircle(i, j)->getStatus() << endl;
			output << *gameboard->getCircle(i, j)->getBuilding()->getCost() << endl;
			output << *gameboard->getCircle(i, j)->getBuilding()->getType() << endl;
		}
	}

}

VGMap* VGMapLoader::load(string fileName) {
	
	try {
		ifstream inputStream(fileName);

		string input;
		inputStream >> input;
		string playerName = input;

		VGMap* gameboard = new VGMap(playerName);

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
				Type resource;
				inputStream >> resource;
				gameboard->getCircle(i, j)->setBuilding(new Building(new Type(resource), new int(stoi(input))));
			}
		}

		inputStream.close();
		return gameboard;
	}

	catch (exception e) {
		cout << "Invalid Save File!";
		return NULL;
	}
}