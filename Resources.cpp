#include <vector>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <map>
#include <limits>
#include "Score.h"
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

void HarvestTile::rotateTile() //rotates harvest tile
{   
    Type* bl = new Type(*this->bottomLeftNode);
    Type* br = new Type(*this->bottomRightNode);
    Type* tl = new Type(*this->topLeftNode);
    Type* tr = new Type(*this->topRightNode);

    this->bottomLeftNode = br;
    this->bottomRightNode = tr;
    this->topLeftNode = bl;
    this->topRightNode = tl;

}

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

        for (int j = 0; j < 6; j++) {
            building = new Building(timberType, cost);
            buildingVector->push_back(building);

            building = new Building(sheepType, cost);
            buildingVector->push_back(building);

            building = new Building(stoneType, cost);
            buildingVector->push_back(building);

            building = new Building(wheatType, cost);
            buildingVector->push_back(building);  
        }              
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

    // 1. Harvest tiles with 2 types, where 2 nodes have same type (12 configurations)
    harvestTilevector->push_back(new HarvestTile(sheepType, stoneType, sheepType, stoneType));
    harvestTilevector->push_back(new HarvestTile(sheepType, stoneType, stoneType, sheepType));
    harvestTilevector->push_back(new HarvestTile(sheepType, timberType, sheepType, timberType));
    harvestTilevector->push_back(new HarvestTile(sheepType, timberType, timberType, sheepType));
    harvestTilevector->push_back(new HarvestTile(sheepType, wheatType, sheepType, wheatType));
    harvestTilevector->push_back(new HarvestTile(sheepType, wheatType, wheatType, sheepType));
    harvestTilevector->push_back(new HarvestTile(stoneType, timberType, stoneType, timberType));
    harvestTilevector->push_back(new HarvestTile(stoneType, timberType, timberType, stoneType));
    harvestTilevector->push_back(new HarvestTile(stoneType, wheatType, stoneType, wheatType));
    harvestTilevector->push_back(new HarvestTile(stoneType, wheatType, wheatType, stoneType));
    harvestTilevector->push_back(new HarvestTile(timberType, wheatType, timberType, wheatType));
    harvestTilevector->push_back(new HarvestTile(timberType, wheatType, wheatType, timberType));

    // 2. harvest tiles with 2 types, where 3 nodes have same type (12 configurations)
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, sheepType, stoneType));
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, sheepType, timberType));
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, sheepType, wheatType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, stoneType, wheatType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, stoneType, sheepType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, stoneType, timberType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, timberType, wheatType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, timberType, sheepType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, timberType, stoneType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, wheatType, stoneType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, wheatType, sheepType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, wheatType, timberType));

    // 3. Harvest tiles with 3 types, where 2 nodes are of same type (36 configurations)
    // 3A. 2 sheep
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, stoneType, timberType));
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, timberType, stoneType));
    harvestTilevector->push_back(new HarvestTile(sheepType, stoneType, timberType, sheepType));
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, wheatType, timberType));
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, timberType, wheatType));
    harvestTilevector->push_back(new HarvestTile(sheepType, wheatType, timberType, sheepType));
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, stoneType, wheatType));
    harvestTilevector->push_back(new HarvestTile(sheepType, sheepType, wheatType, stoneType));
    harvestTilevector->push_back(new HarvestTile(sheepType, stoneType, wheatType, sheepType));
    
    // 3B. 2 stone
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, sheepType, timberType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, timberType, sheepType));
    harvestTilevector->push_back(new HarvestTile(stoneType, sheepType, timberType, stoneType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, wheatType, timberType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, timberType, wheatType));
    harvestTilevector->push_back(new HarvestTile(stoneType, timberType, wheatType, stoneType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, sheepType, wheatType));
    harvestTilevector->push_back(new HarvestTile(stoneType, stoneType, wheatType, sheepType));
    harvestTilevector->push_back(new HarvestTile(stoneType, wheatType, sheepType, stoneType));    

    // 3C. 2 Timber
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, sheepType, stoneType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, stoneType, sheepType));
    harvestTilevector->push_back(new HarvestTile(timberType, stoneType, sheepType, timberType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, sheepType, wheatType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, wheatType, sheepType));
    harvestTilevector->push_back(new HarvestTile(timberType, wheatType, sheepType, timberType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, stoneType, wheatType));
    harvestTilevector->push_back(new HarvestTile(timberType, timberType, wheatType, stoneType));
    harvestTilevector->push_back(new HarvestTile(timberType, stoneType, wheatType, timberType));

    // 3D. 2 Wheat
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, sheepType, stoneType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, stoneType, sheepType));
    harvestTilevector->push_back(new HarvestTile(wheatType, sheepType, stoneType, wheatType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, stoneType, timberType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, timberType, stoneType));
    harvestTilevector->push_back(new HarvestTile(wheatType, timberType, stoneType, wheatType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, sheepType, timberType));
    harvestTilevector->push_back(new HarvestTile(wheatType, wheatType, timberType, sheepType));
    harvestTilevector->push_back(new HarvestTile(wheatType, sheepType, timberType, wheatType));

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

Hand::Hand() {
    sheepResourceMarker = new int(0);
    stoneResourceMarker = new int(0);
    timberResourceMarker = new int(0);
    wheatResourceMarker = new int(0);
    buildings = new vector<Building*>();
    harvestTiles = new vector<HarvestTile*>();
}

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
    while(!(cin >> x_value) || x_value < 0 || x_value >= resourceCounter->getGBMap()->getWidth()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid column. Try again: ";
    }
    cout << "Enter a row: ";
    while(!(cin >> y_value) || y_value < 0 || x_value >= resourceCounter->getGBMap()->getHeight()) {
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
vector<Building*>* Hand::getBuildings() { return buildings; }
vector<HarvestTile*>* Hand::getHarvestTiles() { return harvestTiles; }

void Hand::setShipmentTile(HarvestTile* st) {
    shipmentTile = st;
}

HarvestTile* Hand::getShipmentTile() const {
    return shipmentTile;
}

void Hand::setDeck(Deck* d) {
    deck = d;
}
