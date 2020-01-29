#include <vector>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <map>
#pragma once

using namespace std;

enum class Type {
    Wheat = 0, 
    Sheep, 
    Timber, 
    Stone
};

class Building {
    private:
        Type* type; //wheat, sheep, stone or timber
        int* cost; //cost of building, 1-6
        int* actualCost; // if the player decides to flip it and give it a new cost. This takes precedence over cost, unless 0.

    public:
        Building(Type* t, int* c);
        void setActualCost(int* ac);
        Type* getType();
        int* getCost();
        int* getActualCost();
};

class HarvestTile {
    private:
        Type* topLeftNode;
        Type* topRightNode;
        Type* bottomLeftNode;
        Type* bottomRightNode;

    public:
        HarvestTile(Type* tln, Type* trn, Type* bln, Type* brn);
        Type* getTopLeftNode();
        Type* getTopRightNode();
        Type* getBottomLeftNode();
        Type* getBottomRightNode();

};

class Deck {
    private:
        vector<Building*>* buildingDeck;
        vector<HarvestTile*>* harvestTileDeck;

        // This method will generate all of the buildings needed at the start of the game.
        vector<Building*>* generateBuildings();
        
        // This method will generate all of the harvest tiles needed at the start of the game.
        vector<HarvestTile*>* generateHarvestTiles();

    public:
        Deck();

        Building* drawBuilding();

        HarvestTile* drawHarvestTile();

        vector<Building*>* getBuildingDeck();
        vector<HarvestTile*>* getHarvestTileDeck();
};

class Hand {
    private:
        int* sheepResourceMarker;
        int* stoneResourceMarker;
        int* timberResourceMarker;
        int* wheatResourceMarker;

    public: 
        Hand();

        void exchange(int sheepResources, int stoneResources, 
            int timberResources, int wheatResources);

        int* getSheepResourceMarker();
        int* getStoneResourceMarker();
        int* getTimberResourceMarker();
        int* getWheatResourceMarker();
};

