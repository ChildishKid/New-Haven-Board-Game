#include <iostream>
using namespace std;
#include "GBMaps.h"
#include "GBMapLoader.h"

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

	system("pause");
}