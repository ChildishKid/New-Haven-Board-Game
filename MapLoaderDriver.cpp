#include <iostream>
#include <string>
using namespace std;
#include "GBMaps.h"
#include "GBMapLoader.h"
#include "VGMap.h"
#include "VGMapLoader.h"

int main() {
	string fileName = "BoardGameSave.txt";

	// Create board of player size 3;
	cout << "=== CREATING NEW BOARD GAME OF 3 PLAYERS ===" << endl;
	GBMaps* gameBoardOriginal = new GBMaps(3);
	cout << "DONE!" << endl << endl;

	cout << "=== SETTING RESOURCES ON FIRST SQUARE ===" << endl;
	gameBoardOriginal->getSquare(0, 0)->setBottomLeft(new Type(Type::Wheat));
	gameBoardOriginal->getSquare(0, 0)->setBottomRight(new Type(Type::Stone));
	gameBoardOriginal->getSquare(0, 0)->setTopLeft(new Type(Type::Sheep));
	gameBoardOriginal->getSquare(0, 0)->setTopRight(new Type(Type::Timber));
	cout << "Top Left: " << gameBoardOriginal->getSquare(0, 0)->getTopLeft()->getType() << endl;
	cout << "Top Right: " << gameBoardOriginal->getSquare(0, 0)->getTopRight()->getType() << endl;
	cout << "Bottom Left: " << gameBoardOriginal->getSquare(0, 0)->getBottomLeft()->getType() << endl;
	cout << "Bottom Right: " << gameBoardOriginal->getSquare(0, 0)->getBottomRight()->getType() << endl;
	cout << endl;

	cout << "=== SAVE AND LOAD GAME BOARD ===" << endl;
	GBMapLoader::save(gameBoardOriginal, fileName);
	GBMaps* gameBoardReplace = GBMapLoader::load(fileName);
	cout << "DONE!" << endl << endl;

	cout << "=== DISPLAY RESOURCES ON FIRST SQUARE ===" << endl;
	cout << "Top Left: " << gameBoardReplace->getSquare(0, 0)->getTopLeft()->getType() << endl;
	cout << "Top Right: " << gameBoardReplace->getSquare(0, 0)->getTopRight()->getType() << endl;
	cout << "Bottom Left: " << gameBoardReplace->getSquare(0, 0)->getBottomLeft()->getType() << endl;
	cout << "Bottom Right: " << gameBoardReplace->getSquare(0, 0)->getBottomRight()->getType() << endl;
	cout << endl;

	//Creating new Village Board

	cout << "=== CREATING VILLAGE BOARD ===" << endl;
	cout << "Input name for village board:" << endl;
	string boardName;
	cin >> boardName;

	//Create VGMap object
	VGMap* gameboard = new VGMap(boardName);

	//Changes to VGMap Circle tiles
	cout << "Test: Setting Circle 2,3 to type Wheat, and 3,4 to type Stone" << endl;
	gameboard->getCircle(2, 3)->setType(Type::Wheat);
	gameboard->getCircle(3, 4)->setType(Type::Stone);

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
	cout << "circle 2,3 is type: " << gameboard2->getCircle(2, 3)->getType() << endl;
	cout << "circle 3,4 is type: " << gameboard2->getCircle(3, 4)->getType() << endl;
	cout << "Loading successful" << endl;

	system("pause");
}