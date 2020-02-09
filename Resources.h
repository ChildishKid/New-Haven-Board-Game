#include <vector>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <map>
#pragma once

using namespace std;

// Needed as forward reference.
class ResourceCounter;

enum class Type {
    Wheat = 0, 
    Sheep, 
    Timber, 
    Stone,
    None
};

enum class ResourceType {
    Building = 0,
    HarvestTile
};

class Resource { };

class Building : public Resource {
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

class HarvestTile : public Resource {
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
        Resource* draw(ResourceType ResourceType);
        vector<Building*>* getBuildingDeck();
        vector<HarvestTile*>* getHarvestTileDeck();
};

class Hand {
    private:
        Deck* deck;
        ResourceCounter* resourceCounter;
        int* sheepResourceMarker;
        int* stoneResourceMarker;
        int* timberResourceMarker;
        int* wheatResourceMarker;
        vector<Building*>* buildings;
        vector<HarvestTile*>* harvestTiles;
        void initialize();

    public: 
        Hand(Deck* deck, ResourceCounter* rc);

        void exchange();

        int* getSheepResourceMarker();
        int* getStoneResourceMarker();
        int* getTimberResourceMarker();
        int* getWheatResourceMarker();
        vector<Building*> getBuildings();
        vector<HarvestTile*> getHarvestTiles();
};

