#pragma once
#include <vector>
#include "GBMaps.h"
#include "Score.h"
#include "Player.h"
#include "GameObservers.h"
using namespace std;

// Needed as forward reference.
class ResourceMarkerObserver;
class VillageBuildingObserver;

class Game {
    public:
        Game();
        ~Game();

        void run();
        void calculateScores();

        GBMaps* getGbMap() const;
        vector<Player*>* getPlayers() const;
        vector<Building*>* getBuildingPool() const;
        Deck* getDeck() const;
        map<Type, int> getResourceMarker() const;
    
    private:
        GBMaps* gbMap;
        Deck* deck;
        vector<Player*>* players;
        vector<Building*>* buildingPool;
        map<Type, int>* resourceMarker;
        bool* shipmentTile;
        ResourceCounter* rc;
        ResourceMarkerObserver* resourceMarkerObserver;
        map<Player*, VillageBuildingObserver*>* villageBuildingObservers;

        void setupGBMap();
        void createPlayers();
        void initializeBuildingPool();
        void initializeResources();
        pair<int, int> pickHarvestTile(Player* player);
        bool pickBuildingTile(Player* player);
        void calculateResources(Player* player, pair<int, int> p);


};
