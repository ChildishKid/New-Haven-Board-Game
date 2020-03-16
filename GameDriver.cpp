#include <iostream>
#include <algorithm>
#include "Game.h"
#include "GBMaps.h"

using namespace std;

int main() {
    Game* game = new Game();

    // PART 1
    /*
    cout << "\n======================== VERIFIYING GAME SETUP ========================" << endl;
    cout << "Verifying the number of players..." << endl;
    cout << "Players: " << game->getPlayers()->size() << endl;

    cout << endl << "Verifying the GBMap..." << endl;
    cout << "Players for map: " << game->getGbMap()->getNumberOfPlayers() << endl;
    cout << "Width of map: " << game->getGbMap()->getWidth() << endl;
    cout << "Height of map: " << game->getGbMap()->getHeight() << endl;

    cout << endl << "Verifying the resource markers of game..." << endl;
    cout << "Sheep markers: " << game->getSheepResourceMarker() << endl;
    cout << "Stone markers: " << game->getStoneResourceMarker() << endl;
    cout << "Timber markers: " << game->getTimberResourceMarker() << endl;
    cout << "Wheat markers: " << game->getWheatResourceMarker() << endl;

    cout << endl << "Verifying that the game's building pool has 5 harvest tiles..." << endl;
    cout << "buildingPool size: " << game->getBuildingPool()->size() << endl;

    cout << endl << "Verifying that each player has a valid VGMap, 6 building tiles and 2 harvest tiles..." << endl;
    for(std::vector<Player*>::iterator it = game->getPlayers()->begin(); it != game->getPlayers()->end(); ++it) {
        cout << "Player " << *(*it)->getName() << "..." << endl;
        cout << "GBMap height: " << (*it)->getVGMap()->getHeight() << endl;
        cout << "GBMap width: " << (*it)->getVGMap()->getWidth() << endl;
        cout << "Harvest tiles size: " << (*it)->getPlayersHand()->getHarvestTiles()->size() << endl;
        cout << "Building tiles size: " << (*it)->getPlayersHand()->getBuildings()->size() << endl;
        cout << "Verifying if user has shipment tile: " << *(*it)->getPlayersHand()->getShipmentTile() << endl;
        cout << endl;
    }

    cout << "Verifying deck..." << endl;
    cout << "Given that there are " << game->getPlayers()->size() << " players, there should be: " << endl;
    cout << 60 - (game->getPlayers()->size()*3) << " harvest tiles left, and " << endl;
    cout << 144 - (game->getPlayers()->size()*6) - 5 << " building tiles left." << endl;
    cout << "There are actually: " << endl;
    cout << game->getDeck()->getHarvestTileDeck()->size() << " harvest tiles left, and " << endl;
    cout << game->getDeck()->getBuildingDeck()->size() << " building tiles left." << endl;
    system("pause");
    */

    // PART 2
    /*
    // PART 2.1: Player with smallest ID will begin
    cout << endl << "TURN ORDER:" << endl;
    for (std::vector<Player*>::iterator it = game->getPlayers()->begin(); it != game->getPlayers()->end(); ++it)
        cout << "Player " << *(*it)->getName() << " ("  << *(*it)->getId() << ")..." << endl;
    cout << endl;
    */
    system("pause");
    game->run();
    system("pause");
}