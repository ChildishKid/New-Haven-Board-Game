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

	system("pause");
}