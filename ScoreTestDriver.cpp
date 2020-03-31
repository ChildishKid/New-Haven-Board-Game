#include <iostream>
#include <algorithm>
#include "Game.h"
#include "VGMapLoader.h"

int main() {

	Game* game = new Game();

	vector<Player*>* players = game->getPlayers();

	system("pause");
	cout << " " << endl;
	cout << "Loading completed VGMaps for score testing..." << endl;
	if (players->size() == 2) {
		Player* player1 = players->at(0);
		cout << "Loading " << player1->getName() << "'s VGMap " << endl;
		player1->setPlayersVGMap(VGMapLoader::load("VGMapTest1.txt"));
		Player* player2 = players->at(1);
		cout << "Loading " << player2->getName() << "'s VGMap " << endl;
		player2->setPlayersVGMap(VGMapLoader::load("VGMapTest2.txt"));
		game->
	}
	else if (players->size() == 3) {

	}
	else {


	}



	return 0;
}