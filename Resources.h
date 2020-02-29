#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include "Score.h"
#pragma once

using namespace std;

enum class Type {
    Wheat = 0, 
    Sheep, 
    Timber, 
    Stone,
    None
};

//added operator overload to print enums
std::ostream& operator << (std::ostream& os, const Type& obj)
{
    os << static_cast<std::underlying_type<Type>::type>(obj);
    return os;
}

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
        void rotateTile();

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

        ResourceCounter* getResourceCounter() { return this->resourceCounter; };
        Deck* getDeck() { return this->deck; };
        int* getSheepResourceMarker();
        int* getStoneResourceMarker();
        int* getTimberResourceMarker();
        int* getWheatResourceMarker();
};

inline std::ostream& operator<<(std::ostream& stream, const Type &type) {

    if (Type::Wheat == type) {
        return stream << "Wheat";
    }
    else if (Type::Sheep == type) {
        return stream << "Sheep";
    }
    else if (Type::Timber == type) {
        return stream << "Timber";
    }
    else if (Type::Stone == type) {
        return stream << "Stone";
    }
    else {
        return stream << "None";
    }
}

inline std::ofstream& operator<<(std::ofstream& stream, const Type& type) {

    if (Type::Wheat == type) {
        stream << "Wheat";
    }
    else if (Type::Sheep == type) {
        stream << "Sheep";
    }
    else if (Type::Timber == type) {
        stream << "Timber";
    }
    else if (Type::Stone == type) {
        stream << "Stone";
    }
    else {
        stream << "None";
    }

    return stream;
}

inline std::ifstream& operator>>(std::ifstream& stream, Type& type) {

    string read;
    stream >> read;

    if ("Wheat" == read) {
        type = Type::Wheat;
    }
    else if ("Sheep" == read) {
        type = Type::Sheep;
    }
    else if ("Timber" == read) {
        type = Type::Timber;
    }
    else if ("Stone" == read) {
        type = Type::Stone;
    }
    else {
        type = Type::None;
    }

    return stream;
}