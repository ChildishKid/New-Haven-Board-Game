#pragma once
#include <string>
#include <vector>
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
		map<Type, bool>* hasBuilt;
		int* finalScore;

	public:
		Player();
		Player(string name, int id, GBMaps* gboard);
		Player(Deck* deck, ResourceCounter* rc, GBMaps* gboard);
		void placeHarvestTile(int x, int y); //place tile on specific coordinates
		void placeHarvestTile(int x, int y, HarvestTile* tile); //place tile on specific coordinates
		void drawBuilding();  //add object of Building that has been drawn to players Hand
		void drawHarvestTile(); //add object of HarvestTile that has been drawn to players Hand
		map<string, int> resourceTracker(); //return map for all the resources
		void buildVillage(map<Type, int>* resources); //build village on specific coordinates
		map<Type, int*>* calculateResources(int x, int y);
		void setPlayersVGMap(VGMap* map);
		void setPlayersHand(Hand* h);
		void setPlayersScore(int* score);

		VGMap* getVGMap() { return playersVGMap; }
		Hand* getPlayersHand() { return playersHand; };
		GBMaps* getGBoard() { return gboard; };
		string* getName() { return name; };
		int* getId() { return id; };
		int* getScore() { return finalScore; };

		static bool sortById(Player* one, Player* two);
};