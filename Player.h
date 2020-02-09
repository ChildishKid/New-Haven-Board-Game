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


	public:
		Player();
		void placeOnGBoard();
		void placeHarvestTile(pair<int,int>); //place tile on specific coordinates
		Building* DrawBuilding();  //return object of Building that has been drawn
		HarvestTile* DrawHarvestTile(); //return object of HarvestTile that has been drawn
		map<string, int> ResourceTracker(); //return map for all the resources
		void BuildVillage(pair<int, int>); //build village on specific coordinates
		map<string, int> CalculateResources();
};