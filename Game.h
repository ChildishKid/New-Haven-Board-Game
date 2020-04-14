#pragma once
#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "Score.h"
#include "Player.h"
#include "GameObservers.h"
using namespace std;

// Needed as forward reference.
class ResourceMarkerObserver;
class VillageBuildingObserver;

class Game : public Observable {
    public:
        Game();
        ~Game();

        void run();
        void calculateScores();

        GBMaps* getGbMap() const;
        vector<Player*>* getPlayers() const;
        vector<Building*>* getBuildingPool() const;
        map<Type, int>* getResourceMarker() const;
        Deck* getDeck() const;
        friend std::ostream& operator<<(std::ostream& stream, const Game& game);
    
    private:
        GBMaps* gbMap;
        Deck* deck;
        vector<Player*>* players;
        vector<Building*>* buildingPool;
        map<Type, int>* resourceMarker;
        bool* shipmentTile;
        ResourceCounter* rc;
        map<string, int>* villageBuildingCount; //maps player name to number of village buildings that player has played
        Player* currentPlayer;

        void setupGBMap();
        void createPlayers();
        void initializeBuildingPool();
        void initializeResources();
        pair<int, int> pickHarvestTile(Player* player);
        bool pickBuildingTile(Player* player);
        void calculateResources(Player* player, pair<int, int> p);
};

inline std::ostream& operator<<(std::ostream& stream, const Game& game) {
    stream << *game.currentPlayer->getName() << " is currently playing. " << endl;
    stream << *game.currentPlayer->getName() << " currently has " << (*game.villageBuildingCount)[*game.currentPlayer->getName()]  << " village buildings." << endl;
    stream << "The resource markers are currently set as: " << endl;
    cout << "Sheep: " << (*game.resourceMarker)[Type::Sheep] << endl;
    cout << "Stone: " << (*game.resourceMarker)[Type::Stone] << endl;
    cout << "Timber: " << (*game.resourceMarker)[Type::Timber] << endl;
    cout << "Wheat: " << (*game.resourceMarker)[Type::Wheat] << endl;
    return stream;
}
