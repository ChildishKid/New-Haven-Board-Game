#include <vector>
#include <stdlib.h>
#pragma once

using namespace std;

class Type {
    public:
        enum type {
            Wheat, 
            Sheep, 
            Timber, 
            Stone 
        };
};

class Building {
    private:
        Type::type* type; //wheat, sheep, stone or timber
        int* cost; //cost of building, 1-6
        int* actualCost; // if the player decides to flip it and give it a new cost. This takes precedence over cost, unless null.

    public:
        Building(Type::type* t, int* c) {
            type = t;
            cost = c;
        };
        void setActualCost(int* ac) {
            actualCost = ac;
        };        
        Type::type* getType() { return type; }
        int* getCost() { return cost; }
        int* getActualCost() { return actualCost; }
};

class HarvestTile {
    private:
        Type::type* topLeftNode;
        Type::type* topRightNode;
        Type::type* bottomLeftNode;
        Type::type* bottomRightNode;

    public:
        HarvestTile(Type::type* tln, 
                    Type::type* trn, 
                    Type::type* bln, 
                    Type::type* brn) {

            topLeftNode = tln;
            topRightNode = trn;
            bottomLeftNode = bln;
            bottomRightNode = brn;
        };
        Type::type* getTopLeftNode() { return topLeftNode; }
        Type::type* getTopRightNode() { return topRightNode; }
        Type::type* getBottomLeftNode() { return bottomLeftNode; }
        Type::type* getBottomRightNode() { return bottomRightNode; }

};

class Deck {
    private:
        vector<Building*>* buildingDeck;
        vector<HarvestTile*>* harvestTileDeck;

        // This method will generate all of the buildings needed at the start of the game.
        vector<Building*>* generateBuildings() {
            vector<Building*>* buildingVectorPointer;
            vector<Building*> buildingVector = {};
            for (int cost = 1; cost < 7; cost = cost + 1) {
                Type::type type = Type::type::Timber;
                Type::type* typePtr = &type;
                Building building = Building(typePtr, &cost);
                buildingVector.push_back(&building);

                type = Type::type::Stone;
                building = Building(typePtr, &cost);
                buildingVector.push_back(&building);

                type = Type::type::Sheep;
                building = Building(typePtr, &cost);
                buildingVector.push_back(&building);

                type = Type::type::Wheat;
                building = Building(typePtr, &cost);
                buildingVector.push_back(&building);
            }
            buildingVectorPointer = &buildingVector;
            return buildingVectorPointer;
        }
        
        // This method will generate all of the harvest tiles needed at the start of the game.
        // Emailed professor about the harvest tiles, no algorithm devised yet for the generation.
        vector<HarvestTile*>* generateHarvestTiles() {
            vector<HarvestTile*>* harvestTilevectorPointer = {};
            vector<HarvestTile*> harvestTilevector = {};
            Type::type type = Type::type::Timber;
            Type::type* typePtr = &type;
            for (int i=0; i<60 ; i++) {
                HarvestTile harvestTile = HarvestTile(typePtr, typePtr, typePtr, typePtr);
                harvestTilevector.push_back(&harvestTile);
            }
            harvestTilevectorPointer = &harvestTilevector;
            return harvestTilevectorPointer;
        }

    public:
        Deck() {
            buildingDeck = generateBuildings();
            harvestTileDeck = generateHarvestTiles();
        }

        Building* drawBuilding() {
            vector<Building*> buildings = *getBuildingDeck();
            int randomIndex = rand() % buildings.capacity();
            Building* pickedBuilding = buildings[randomIndex];
            buildings.erase(buildings.begin() + randomIndex);
            return pickedBuilding;
        }

        HarvestTile* drawHarvestTile() {
            vector<HarvestTile*> harvestTiles = *getHarvestTileDeck();
            int randomIndex = rand() % sizeof(harvestTiles);
            HarvestTile* pickedHarvestTile = harvestTiles[randomIndex];
            harvestTiles.erase(harvestTiles.begin() + randomIndex);
            return pickedHarvestTile; 
        }

        vector<Building*>* getBuildingDeck() { return buildingDeck; }
        vector<HarvestTile*>* getHarvestTileDeck() { return harvestTileDeck; }
};

class Hand {
    private:
        int* sheepResourceMarker;
        int* stoneResourceMarker;
        int* timberResourceMarker;
        int* wheatResourceMarker;

    public: 
        Hand() {
            int zero = 0;
            Hand::sheepResourceMarker = &zero;
            Hand::stoneResourceMarker = &zero;
            Hand::timberResourceMarker = &zero;
            Hand::wheatResourceMarker = &zero;
        }

        void exchange(int sheepResources, int stoneResources, 
            int timberResources, int wheatResources) {
                int newSheepResourceMarker = *Hand::sheepResourceMarker + sheepResources;
                Hand::sheepResourceMarker = &newSheepResourceMarker;
                
                int newStoneResourceMarker = *Hand::stoneResourceMarker + stoneResources;
                Hand::stoneResourceMarker = &newStoneResourceMarker;

                int newTimberResourceMarker = *Hand::timberResourceMarker + timberResources;
                Hand::timberResourceMarker = &newTimberResourceMarker;

                int newWheatResourceMarker = *Hand::wheatResourceMarker + wheatResources;
                Hand::wheatResourceMarker = &newWheatResourceMarker;
        }

        int* getSheepResourceMarker() { return sheepResourceMarker; }
        int* getStoneResourceMarker() { return stoneResourceMarker; }
        int* getTimberResourceMarker() { return timberResourceMarker; }
        int* getWheatResourceMarker() { return wheatResourceMarker; }
};

