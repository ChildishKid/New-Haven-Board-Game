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
        int* actualCost; // if the player decides to flip it and give it a new cost. This takes precedence over cost, unless null.

    public:
        Building(Type* t, int* c) {
            type = t;
            cost = c;
            actualCost = new int();
            *actualCost = 0;
        };
        void setActualCost(int* ac) {
            actualCost = ac;
        };        
        Type* getType() { return type; }
        int* getCost() { return cost; }
        int* getActualCost() { return actualCost; }
};

class HarvestTile {
    private:
        Type* topLeftNode;
        Type* topRightNode;
        Type* bottomLeftNode;
        Type* bottomRightNode;

    public:
        HarvestTile(Type* tln, 
                    Type* trn, 
                    Type* bln, 
                    Type* brn) {

            topLeftNode = tln;
            topRightNode = trn;
            bottomLeftNode = bln;
            bottomRightNode = brn;
        };
        Type* getTopLeftNode() { return topLeftNode; }
        Type* getTopRightNode() { return topRightNode; }
        Type* getBottomLeftNode() { return bottomLeftNode; }
        Type* getBottomRightNode() { return bottomRightNode; }

};

class Deck {
    private:
        vector<Building*>* buildingDeck;
        vector<HarvestTile*>* harvestTileDeck;

        // This method will generate all of the buildings needed at the start of the game.
        vector<Building*>* generateBuildings() {
            vector<Building*>* buildingVector = new vector<Building*>();
            Type* timberType = new Type{Type::Timber};
            Type* sheepType = new Type{Type::Sheep};
            Type* stoneType = new Type{Type::Stone};
            Type* wheatType = new Type{Type::Wheat};
            int* cost;
            Building* building;

            for (int i = 0; i < 6; i++) {
                cost = new int(i+1);
                building = new Building(timberType, cost);
                buildingVector->push_back(building);

                building = new Building(sheepType, cost);
                buildingVector->push_back(building);

                building = new Building(stoneType, cost);
                buildingVector->push_back(building);

                building = new Building(wheatType, cost);
                buildingVector->push_back(building);                
            }
            return buildingVector;
        }
        
        // This method will generate all of the harvest tiles needed at the start of the game.
        vector<HarvestTile*>* generateHarvestTiles() {
            vector<HarvestTile*>* harvestTilevector = new vector<HarvestTile*>();
            Type* timberType = new Type{Type::Timber};
            Type* sheepType = new Type{Type::Sheep};
            Type* stoneType = new Type{Type::Stone};
            Type* wheatType = new Type{Type::Wheat};
            HarvestTile* harvestTile;
            vector<Type*>* types = new vector<Type*>(); // vector pointer of all types
            types->push_back(sheepType);
            types->push_back(stoneType);
            types->push_back(timberType);
            types->push_back(wheatType);
            map<Type*, int*>* typeMap = new map<Type*, int*>(); // map to keep track of types of a tile and how many times they are part of a tile
            vector<Type*>* nodeTypes = new vector<Type*>(); // the list of types that a harvest tile will have (each one associated to a node)
            Type* type = types->at(0); // the randomly generated type

            for (int i=0; i<60 ; i++) {
                nodeTypes->clear(); // clear vector every iteration
                typeMap->clear(); // clear map every iteration
                while (nodeTypes->size() < 5) { // while 4 types haven't been selected for the tile
	                type = types->at(rand() % types->size()); // randomly select a type
                    if (nodeTypes->size() > 0 && // if no type was yet selected and...
                        ((typeMap->find(type) != typeMap->end() && *(*typeMap)[type] == 3) // the randomly generated type has already been selected 3 times for the tile (at least 2 types per tile)
                            || (typeMap->find(type) == typeMap->end() && typeMap->size() == 3))) { // the map size is 3 and the newly generated type is not part of the map (max 3 types per tile)
                        continue;
                    } else { // else push the randomly generated type to the vector and add it to the map with its count
                        nodeTypes->push_back(new Type{*type});
                        if (typeMap->find(type) == typeMap->end()) {
                            (*typeMap)[type] = new int();
                            *(*typeMap)[type] = 1;
                        } else {
                            *(*typeMap)[type] = *(*typeMap)[type] + 1;
                        }
                    }
                }
                harvestTile = new HarvestTile(nodeTypes->at(0), nodeTypes->at(1), nodeTypes->at(2), nodeTypes->at(3));
                harvestTilevector->push_back(harvestTile);
            }
            *harvestTilevector;
            return harvestTilevector;
        }

    public:
        Deck() {
            srand(time(NULL)); // This is to make ran() random.
            buildingDeck = new vector<Building*>();
            buildingDeck = generateBuildings();
            harvestTileDeck = new vector<HarvestTile*>();
            harvestTileDeck = generateHarvestTiles();
        }

        Building* drawBuilding() {
            vector<Building*>* buildings = new vector<Building*>();
            buildings = getBuildingDeck();
            int randomIndex = rand() % buildings->size();
            Building* pickedBuilding = buildings->at(randomIndex);
            buildings->erase(buildings->begin() + randomIndex);
            *buildings;
            return pickedBuilding;
        }

        HarvestTile* drawHarvestTile() {
            vector<HarvestTile*>* harvestTiles = new vector<HarvestTile*>();
            harvestTiles = getHarvestTileDeck();
            int randomIndex = rand() % harvestTiles->size();
            HarvestTile* pickedHarvestTile = harvestTiles->at(randomIndex);
            harvestTiles->erase(harvestTiles->begin() + randomIndex);
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

