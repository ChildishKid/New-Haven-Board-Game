#include <vector>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <map>
#include <limits>
#include "Resources.h"

using namespace std;

Building::Building(Type* t, int* c) {
    type = t;
    cost = c;
    actualCost = new int();
    *actualCost = 0;
};

void Building::setActualCost(int* ac) {
    actualCost = ac;
};        

Type* Building::getType() { return type; }

int* Building::getCost() { return cost; }

int* Building::getActualCost() { return actualCost; }

HarvestTile::HarvestTile(Type* tln, Type* trn, Type* bln, Type* brn) {
    topLeftNode = tln;
    topRightNode = trn;
    bottomLeftNode = bln;
    bottomRightNode = brn;
};

Type* HarvestTile::getTopLeftNode() { return topLeftNode; }
Type* HarvestTile::getTopRightNode() { return topRightNode; }
Type* HarvestTile::getBottomLeftNode() { return bottomLeftNode; }
Type* HarvestTile::getBottomRightNode() { return bottomRightNode; }

// This method will generate all of the buildings needed at the start of the game.
vector<Building*>* Deck::generateBuildings() {
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
vector<HarvestTile*>* Deck::generateHarvestTiles() {
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
            type = types->at(rand() % (types->size() - 1)); // randomly select a type
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

Deck::Deck() {
    srand(time(NULL)); // This is to make ran() random.
    buildingDeck = new vector<Building*>();
    buildingDeck = generateBuildings();
    harvestTileDeck = new vector<HarvestTile*>();
    harvestTileDeck = generateHarvestTiles();
}

Resource* Deck::draw(ResourceType resourceType) {
    if (resourceType == ResourceType::Building) {
        vector<Building*>* buildings = new vector<Building*>();
        buildings = getBuildingDeck();
        int randomIndex = rand() % buildings->size();
        Building* pickedBuilding = buildings->at(randomIndex);
        buildings->erase(buildings->begin() + randomIndex);
        *buildings;
        return pickedBuilding;
    } else {
        vector<HarvestTile*>* harvestTiles = new vector<HarvestTile*>();
        harvestTiles = getHarvestTileDeck();
        int randomIndex = rand() % harvestTiles->size();
        HarvestTile* pickedHarvestTile = harvestTiles->at(randomIndex);
        harvestTiles->erase(harvestTiles->begin() + randomIndex);
        return pickedHarvestTile; 
    }
}

vector<Building*>* Deck::getBuildingDeck() { return buildingDeck; }
vector<HarvestTile*>* Deck::getHarvestTileDeck() { return harvestTileDeck; }

Hand::Hand(Deck* d, ResourceCounter* rc) {
    deck = d;
    resourceCounter = rc;
    sheepResourceMarker = new int(0);
    stoneResourceMarker = new int(0);
    timberResourceMarker = new int(0);
    wheatResourceMarker = new int(0);
    buildings = new vector<Building*>();
    harvestTiles = new vector<HarvestTile*>();
    initialize();
}

// 
void Hand::initialize() {
    // Draw 6 buildings and 2 harvest tiles
    for (int i = 0 ; i < 6 ; i++) {
        buildings->push_back(static_cast<Building*>(deck->draw(ResourceType::Building)));
    }
    harvestTiles->push_back(static_cast<HarvestTile*>(deck->draw(ResourceType::HarvestTile)));
    harvestTiles->push_back(static_cast<HarvestTile*>(deck->draw(ResourceType::HarvestTile)));
}

void Hand::exchange() {
    int x_value, y_value;
    cout << "Enter a column: ";
    while(!(cin >> x_value) || x_value < 0 || x_value >= resourceCounter->getGBMap().getWidth()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid column. Try again: ";
    }
    cout << "Enter a row: ";
    while(!(cin >> y_value) || y_value < 0 || x_value >= resourceCounter->getGBMap().getHeight()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid row. Try again: ";
    }
    map<Type, int*>* calculatedResources = new map<Type, int*>();
    calculatedResources = resourceCounter->calculateCollectedResources(x_value, y_value);
    *sheepResourceMarker = *sheepResourceMarker + *(*calculatedResources)[Type::Sheep];
    *stoneResourceMarker = *stoneResourceMarker + *(*calculatedResources)[Type::Stone];
    *timberResourceMarker = *timberResourceMarker + *(*calculatedResources)[Type::Timber];
    *wheatResourceMarker = *wheatResourceMarker + *(*calculatedResources)[Type::Wheat];
}

int* Hand::getSheepResourceMarker() { return sheepResourceMarker; }
int* Hand::getStoneResourceMarker() { return stoneResourceMarker; }
int* Hand::getTimberResourceMarker() { return timberResourceMarker; }
int* Hand::getWheatResourceMarker() { return wheatResourceMarker; }
vector<Building*> Hand::getBuildings() { return *buildings; }
vector<HarvestTile*> Hand::getHarvestTiles() { return *harvestTiles; }

