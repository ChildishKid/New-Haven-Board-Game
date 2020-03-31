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

		void displayGameBoard() const;
		void displayBuidlingPool() const;
		void displayVillageBoard(Player* player) const;
		void displayPlayerHand(Player* player) const;

		void calculateScores();
		void displayWinner();
    
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
        bool shipmentTile;


        pair<int,int> pickHarvestTile(Player* player);
        bool pickBuildingTile(Player* player);

		void calculateResources(Player* player, pair<int,int> p);

};
