#include <vector>
#include <iostream>
using namespace std;
#include "GBMaps.h"

int main() {

	for (int x = 2; x <= 4; x++) {

		cout << "=== ADJACENCY TEST FOR " << x << " PLAYERS ===" << endl;

		// Create game board map and initialize all squares to default (i.e. emtpy values)
		map<pair<int, int>, GBMaps::Square*> gameBoard = GBMaps::setUpBoard(x);

		// Create iterator to go through each element of map
		map<pair<int, int>, GBMaps::Square*>::iterator iterate = gameBoard.begin();

		// Display edges/connections of each squares
		for (; iterate != gameBoard.end(); ++iterate) {

			// Create adjency vectors for each sqaure
			vector<GBMaps::Square*> adj = iterate->second->getAdj();

			// Display edges
			cout << "(" << iterate->second->getX() << ", " << iterate->second->getY() << ")";
			for (int i = 0; i < iterate->second->getSize(); i++) {
				GBMaps::Square* s = adj.at(i);
				cout << " -> (" << s->getX() << ", " << s->getY() << ")";
			}
			cout << endl;
		}

		cout << endl << endl;
	}
	system("pause");
}