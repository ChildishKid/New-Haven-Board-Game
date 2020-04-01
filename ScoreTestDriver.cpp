#include <iostream>
#include <algorithm>
#include "Game.h"
#include "VGMapLoader.h"
#include "Display.h"

int main() {

	cout << "===== Testing calculateScore() and displayWinner() =====" << endl;
	cout << " " << endl;

	Game* game = new Game();

	vector<Player*>* players = game->getPlayers();

	system("pause");
	cout << " " << endl;
	cout << "Loading completed VGMaps for score testing..." << endl;
	if (players->size() == 2) {
		//Load the test final maps for players 1 & 2
		//Checks the functionality that compares scores
		Player* player1 = players->at(0);
		cout << "Loading " << *player1->getName() << "'s VGMap " << endl;
		player1->setPlayersVGMap(VGMapLoader::load("VGMapTest1.txt"));
		Display::displayVillageBoard(player1);
		cout << " " << endl;
		Player* player2 = players->at(1);
		cout << "Loading " << *player2->getName() << "'s VGMap " << endl;
		player2->setPlayersVGMap(VGMapLoader::load("VGMapTest2.txt"));
		Display::displayVillageBoard(player2);
		
		game->calculateScores();
		Display::displayWinner(game->getPlayers());
	}
	else if (players->size() == 3) {
		//Load test maps for three players
		//Tests if the tie breaker works
		Player* player1 = players->at(0);
		cout << "Loading " << *player1->getName() << "'s VGMap " << endl;
		player1->setPlayersVGMap(VGMapLoader::load("VGMapTest1.txt"));
		Display::displayVillageBoard(player1);
		cout << " " << endl;
		Player* player2 = players->at(1);
		cout << "Loading " << *player2->getName() << "'s VGMap " << endl;
		player2->setPlayersVGMap(VGMapLoader::load("VGMapTest2.txt"));
		Display::displayVillageBoard(player2);
		Player* player3 = players->at(2);
		cout << "Loading " << *player3->getName() << "'s VGMap " << endl;
		player3->setPlayersVGMap(VGMapLoader::load("VGMapTest3.txt"));
		Display::displayVillageBoard(player3);

		game->calculateScores();
		Display::displayWinner(game->getPlayers());
	}
	else {

		//Load maps for four players, player 3 and player 4 have identical maps
		//Test to see display in case of a tie (between 3 and 4)
		Player* player1 = players->at(0);
		cout << "Loading " << *player1->getName() << "'s VGMap " << endl;
		player1->setPlayersVGMap(VGMapLoader::load("VGMapTest1.txt"));
		Display::displayVillageBoard(player1);
		cout << " " << endl;
		Player* player2 = players->at(1);
		cout << "Loading " << *player2->getName() << "'s VGMap " << endl;
		player2->setPlayersVGMap(VGMapLoader::load("VGMapTest2.txt"));
		Display::displayVillageBoard(player2);
		Player* player3 = players->at(2);
		cout << "Loading " << *player3->getName() << "'s VGMap " << endl;
		player3->setPlayersVGMap(VGMapLoader::load("VGMapTest3.txt"));
		Display::displayVillageBoard(player3);
		Player* player4 = players->at(3);
		cout << "Loading " << *player4->getName() << "'s VGMap " << endl;
		player4->setPlayersVGMap(VGMapLoader::load("VGMapTest3.txt"));
		Display::displayVillageBoard(player4);

		game->calculateScores();
		Display::displayWinner(game->getPlayers());

	}

	system("pause");

	return 0;
}