#include <vector>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <map>
#pragma once

using namespace std;

enum class Type {
    Wheat, 
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
            vector<Type> types{*sheepType, *stoneType, *timberType, *wheatType};
            map<Type, int> map = {};
            Type lastSelection = types.at(0);
            vector<Type> nodeTypes = {};
            Type type = types.at(0);

            for (int i=0; i<60 ; i++) {
                nodeTypes.clear();
                map.clear();
                while (nodeTypes.size() < 5) {
	                type = types.at(rand() % types.size());
                    if (nodeTypes.size() > 0 && (lastSelection == type || (map.find(type) == map.end() && map.size() == 3))) {
                        continue;
                    } else {
                        lastSelection = type;
                        nodeTypes.push_back(lastSelection);
                        if (map.find(type) == map.end()) {
                            map[type] = 1;
                        } else {
                            map[type] = map[type] + 1;
                        }
                    }
                }
                harvestTile = new HarvestTile(&types.at(0), &types.at(1), &types.at(2), &types.at(3));
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

