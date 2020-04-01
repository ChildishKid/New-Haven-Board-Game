#pragma once
#include <vector>
#include "GBMaps.h"
#include "Score.h"
#include "Player.h"
using namespace std;

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
    
    private:
        GBMaps* gbMap;
        Deck* deck;
        vector<Player*>* players;
        vector<Building*>* buildingPool;
        map<Type, int>* resourceMarker;
        bool* shipmentTile;
        ResourceCounter* rc;

        void setupGBMap();
        void createPlayers();
        void initializeBuildingPool();
        void initializeResources();
        pair<int, int> pickHarvestTile(Player* player);
        bool pickBuildingTile(Player* player);
        void calculateResources(Player* player, pair<int, int> p);


};
