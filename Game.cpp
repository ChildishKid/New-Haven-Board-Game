#include <iostream>
#include <string>
#include <limits>
#include <map>
#include "Game.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
using namespace std;

Game::Game() {
    setupGBMap();
    cout << "Creating a deck with 144 building tiles and 60 harvest tiles..." << endl;
    deck = new Deck();
    initializeBuildingPool();
    createPlayers();
    initializeResources();
};

void Game::setupGBMap() {
    int numOfPlayers;
    cout << "Please enter the number of players (2-4): ";

    while(!(cin >> numOfPlayers) || numOfPlayers < 2 || numOfPlayers > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 2 and 4: ";
    }

    cout << "Setting up the correct GBMap..." << endl;
    if (numOfPlayers == 2) {
        Game::gbMap = GBMapLoader::load("TwoPlayersGBMap.txt");
    } else  if (numOfPlayers == 3) {
        Game::gbMap = GBMapLoader::load("ThreePlayersGBMap.txt");
    } else {
        Game::gbMap = GBMapLoader::load("FourPlayersGBMap.txt");
    }
};

void Game::createPlayers() {
    string name;
    players = new vector<Player*>();
    for (int i=0; i < gbMap->getNumberOfPlayers(); i++) {
        cout << "Please enter the name of player " << i + 1 << ": ";
        cin >> name;
        Player* player = new Player(name);

        cout << "Creating " << name << "'s empty hand..." << endl;
        Hand* hand = new Hand();
        hand->setDeck(deck);
        player->setPlayersHand(hand);

        cout << "Setting " << name << "'s VGMap..." << endl;
        player->setPlayersVGMap(VGMapLoader::load("VGMap.txt"));

        cout << "Drawing " << name << "'s 6 buildings..." << endl;     
        for (int j=0; j < 6; j++) {
            player->drawBuilding();
        }

        cout << "Drawing " << name << "'s 2 harvest tiles..." << endl;     
        for (int j=0; j<2; j++) {
            player->drawHarvestTile();
        }

        cout << "Drawing " << name << "'s shipment tile..." << endl;     
        player->getPlayersHand()->setShipmentTile(
            static_cast<HarvestTile*>(deck->draw(ResourceType::HarvestTile)));
            
        players->insert(players->begin(), player);
    }
};

void Game::initializeBuildingPool() {
    cout << "Drawing 5 building tiles and placing them in the pool..." << endl;
    buildingPool = new vector<Building*>();
    for (int i=0; i < 5; i++) {
        buildingPool->push_back(static_cast<Building*>(deck->draw(ResourceType::Building)));
    }
}

void Game::initializeResources() {
    cout << "Using resourceTracker to set game's resources markers..." << endl;
    map<string, int> resources = players->front()->resourceTracker();
    sheepResourceMarker = new int(resources["Sheep"]);
    stoneResourceMarker = new int(resources["Stone"]);
    timberResourceMarker = new int(resources["Timber"]);
    wheatResourceMarker = new int(resources["Wheat"]);
}

GBMaps* Game::getGbMap() const {
    return gbMap;
}

vector<Player*>* Game::getPlayers() const {
    return players;
}

vector<Building*>* Game::getBuildingPool() const {
    return buildingPool;
}

int Game::getSheepResourceMarker() const {
    return *sheepResourceMarker;
}

int Game::getStoneResourceMarker() const {
    return *stoneResourceMarker;
}

int Game::getTimberResourceMarker() const {
    return *timberResourceMarker;
}

int Game::getWheatResourceMarker() const {
    return *wheatResourceMarker;
}

Deck* Game::getDeck() const {
    return deck;
}
