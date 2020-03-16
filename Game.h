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
        void setSheepResourceMarker(int s);
        void setStoneResourceMarker(int s);
        void setTimberResourceMarker(int s);
        void setWheatResourceMarker(int s);
        GBMaps* getGbMap() const;
        vector<Player*>* getPlayers() const;
        vector<Building*>* getBuildingPool() const;
        Deck* getDeck() const;

        void run();
    
    private:
        void setupGBMap();
        void createPlayers();
        void initializeBuildingPool();
        void initializeResources();
        string typePrefix(Type type) const;
        GBMaps* gbMap;
        Deck* deck;
        vector<Player*>* players;
        vector<Building*>* buildingPool;
        int* sheepResourceMarker;
        int* stoneResourceMarker;
        int* timberResourceMarker;
        int* wheatResourceMarker;

        void displayGameBoard() const;
        void displayVillageBoard(Player* player) const;
        void displayPlayerHand(Player* player) const;
        void pickHarvestTile(Player* player);
};
