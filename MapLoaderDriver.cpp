#include <iostream>
#include <string>
using namespace std;
#include "GBMaps.h"
#include "GBMapLoader.h"
#include "VGMap.h"
#include "VGMapLoader.h"

int main() {

	// Create board of player size 3;
	cout << "=== CREATING NEW BOARD GAME OF 3 PLAYERS ===" << endl;
	GBMaps* gameBoardOriginal = new GBMaps(3);

	// Display edges/connections of each squares
	for (; gameBoardOriginal->iterate != gameBoardOriginal->end(); ++gameBoardOriginal->iterate) {
		// Display edges
		cout << "(" << gameBoardOriginal->iterate->second->getX() << ", " << gameBoardOriginal->iterate->second->getY() << ")";
		for (int i = 0; i < gameBoardOriginal->iterate->second->getSize(); i++) {
			GBMaps::Square* s = gameBoardOriginal->iterate->second->getAdj().at(i);
			cout << " -> (" << s->getX() << ", " << s->getY() << ")";
		}
		cout << endl;
	}
	cout << endl << endl;

	cout << "=== LOADED GAME BOARD ===" << endl;
	GBMapLoader::save(gameBoardOriginal);
	GBMaps* gameBoardReplace = GBMapLoader::load();

	gameBoardReplace->iterate = gameBoardReplace->begin();

	// Display edges/connections of each squares
	for (; gameBoardReplace->iterate != gameBoardReplace->end(); ++gameBoardReplace->iterate) {
		// Display edges
		cout << "(" << gameBoardReplace->iterate->second->getX() << ", " << gameBoardReplace->iterate->second->getY() << ")";
		for (int i = 0; i < gameBoardReplace->iterate->second->getSize(); i++) {
			GBMaps::Square* s = gameBoardReplace->iterate->second->getAdj().at(i);
			cout << " -> (" << s->getX() << ", " << s->getY() << ")";
		}
		cout << endl;
	}
	cout << endl << endl;

	//Creating new Village Board

	cout << "=== CREATING VILLAGE BOARD ===" << endl;
	cout << "Input name for village board:" << endl;
	string boardName;
	cin >> boardName;

	//Create VGMap object
	VGMap* gameboard = new VGMap(boardName);

	//Changes to VGMap Circle tiles
	cout << "Test: Setting Circle 2,3 to type Wheat, and 3,4 to type Stone" << endl;
	gameboard->getCircle(2, 3)->setTypeString("Wheat");
	gameboard->getCircle(3, 4)->setTypeString("Stone");

	//Saving gameboard
	cout << "Input name of the save file (with the .txt suffix):" << endl;
	string saveFile;
	cin >> saveFile;
	cout << "Saving gameboard to " << saveFile << endl;
	VGMapLoader::save(gameboard, saveFile);

	//loading new gameboard from save file
	cout << "Input name of saved file to load (include .txt suffix) :" << endl;
	string loadFile;
	cin >> loadFile;
	VGMap* gameboard2 = VGMapLoader::load(loadFile);
	cout << "Loading " << loadFile << endl;
	
	//testing the loaded map
	cout << "Test: checking the types loaded map for circle 2,3 and circle 3,4" << endl;
	cout << "circle 2,3 is type: " << gameboard2->getCircle(2, 3)->getTypeString() << endl;
	cout << "circle 3,4 is type: " << gameboard2->getCircle(3, 4)->getTypeString() << endl;
	cout << "Loading successful" << endl;

	system("pause");
}