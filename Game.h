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
        int getSheepResourceMarker() const;
        int getStoneResourceMarker() const;
        int getTimberResourceMarker() const;
        int getWheatResourceMarker() const;
        void setSheepResourceMarker(int s) const;
        void setStoneResourceMarker(int s) const;
        void setTimberResourceMarker(int s) const;
        void setWheatResourceMarker(int s) const;
        GBMaps* getGbMap() const;
        vector<Player*>* getPlayers() const;
        vector<Building*>* getBuildingPool() const;
        Deck* getDeck() const;
    
    private:
        void setupGBMap();
        void createPlayers();
        void initializeBuildingPool();
        void initializeResources();
        GBMaps* gbMap;
        Deck* deck;
        vector<Player*>* players;
        vector<Building*>* buildingPool;
        int* sheepResourceMarker;
        int* stoneResourceMarker;
        int* timberResourceMarker;
        int* wheatResourceMarker;
};
