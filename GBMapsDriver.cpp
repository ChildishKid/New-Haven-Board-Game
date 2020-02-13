#include <vector>
#include <iostream>
using namespace std;
#include "GBMaps.h"

int main() {

	GBMaps* gameBoard;

	for (int x = 2; x <= 4; x++) {

		cout << "=== ADJACENCY TEST FOR " << x << " PLAYERS ===" << endl;

		// Create game board map and initialize all squares to default (i.e. emtpy values)
		gameBoard = new GBMaps(x);
		// Display edges/connections of each squares
		for (; gameBoard->iterate != gameBoard->end(); ++gameBoard->iterate) {
			// Display edges
			cout << "(" << gameBoard->iterate->second->getX() << ", " << gameBoard->iterate->second->getY() << ")";
			for (int i = 0; i < gameBoard->iterate->second->getSize(); i++) {
				GBMaps::Square* s = gameBoard->iterate->second->getAdj().at(i);
				cout << " -> (" << s->getX() << ", " << s->getY() << ")";
			}
			cout << endl;
		}
		cout << endl << endl;
	}

	//CFile file;
	//file.Open(_T("Sample.txt"), CFile::modeCreate | CFile::modeWrite);
	//CArchive archive(&file, CArchive::store);
	//gameBoard->Serialize(archive);
	//archive.Close();
	//file.Close();
	//
	//CFile readFile;
	//readFile.Open(_T("Sample.txt"), CFile::modeRead);
	//CArchive readArchive(&readFile, CArchive::load);
	//GBMaps* gameBoardRead = new GBMaps();
	//gameBoardRead->Serialize(readArchive);
	//gameBoard->saveGame();
	//GBMaps* gameBoardRead = new GBMaps();
	//gameBoardRead->loadGame();

	//for (; gameBoardRead->iterate != gameBoardRead->end(); ++gameBoardRead->iterate) {
	//	// Display edges
	//	cout << "(" << gameBoardRead->iterate->second->getX() << ", " << gameBoardRead->iterate->second->getY() << ")";
	//	for (int i = 0; i < gameBoardRead->iterate->second->getSize(); i++) {
	//		GBMaps::Square* s = gameBoardRead->iterate->second->getAdj().at(i);
	//		cout << " -> (" << s->getX() << ", " << s->getY() << ")";
	//	}
	//	cout << endl;
	//}

	system("pause");
}