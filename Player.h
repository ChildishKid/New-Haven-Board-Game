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

	public:
		Player();
		Player(Deck* deck, ResourceCounter* rc, GBMaps* gboard);
		void placeHarvestTile(int x, int y); //place tile on specific coordinates
		void DrawBuilding();  //add object of Building that has been drawn to players Hand
		void DrawHarvestTile(); //add object of HarvestTile that has been drawn to players Hand
		map<string, int> ResourceTracker(); //return map for all the resources
		void BuildVillage(int x, int y); //build village on specific coordinates
		map<Type, int*>* CalculateResources(int x, int y);

		VGMap* getVGMap() { return playersVGMap; }
		Hand* getPlayersHand() { return playersHand; };
		GBMaps* getGBoard() { return gboard; };
};