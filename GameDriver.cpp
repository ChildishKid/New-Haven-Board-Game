#include <iostream>
#include <algorithm>
#include "Game.h"
#include "GBMaps.h"
#include "GameObservers.h"
using namespace std;

int main() {
    Game* game = new Game();
    GameStatisticsObserver* gsObserver = new GameStatisticsObserver(game);
    GameObserver* gObserver = new GameObserver(game);
    TurnObserver* tObserver = new TurnObserver(game);

    system("pause");
    game->run();
    system("CLS");
    gsObserver->display("end");
    system("pause");
    delete gsObserver;
    delete gObserver;
    delete tObserver;
    delete game;
    game = NULL;
    gsObserver = NULL;
    gObserver = NULL;
    tObserver = NULL;
}