#pragma once
#include "Player.h"

namespace Display {
	void displayGameBoard(GBMaps* gbMap, map<Type, int>* resourceMarker);
	void displayBuidlingPool(vector<Building*>* buildingPool);
	void displayVillageBoard(Player* player);
	void displayPlayerHand(Player* player);
	void displayWinner(vector<Player*>* players);
	string typePrefix(Type type);
}