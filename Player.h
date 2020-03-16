#pragma once
#include <string>
#include <vector>
#include <map>
#include "Resources.h"
#include "GBMaps.h"
#include "VGMap.h"


class Player {
	private:
		Hand* playersHand;
		VGMap* playersVGMap;
		GBMaps* gboard;
		string* name;
		int* id;

	public:
		Player();
		Player(string name, int id);
		Player(Deck* deck, ResourceCounter* rc, GBMaps* gboard);
		void placeHarvestTile(int x, int y); //place tile on specific coordinates
		void drawBuilding();  //add object of Building that has been drawn to players Hand
		void drawHarvestTile(); //add object of HarvestTile that has been drawn to players Hand
		map<string, int> resourceTracker(); //return map for all the resources
		void buildVillage(int x, int y); //build village on specific coordinates
		map<Type, int*>* calculateResources(int x, int y);
		void setPlayersVGMap(VGMap* map);
		void setPlayersHand(Hand* h);

		VGMap* getVGMap() { return playersVGMap; }
		Hand* getPlayersHand() { return playersHand; };
		GBMaps* getGBoard() { return gboard; };
		string* getName() { return name; };
		int* getId() { return id; };

		static bool sortById(Player* one, Player* two);
};