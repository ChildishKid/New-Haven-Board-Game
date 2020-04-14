#include <iostream>
#include <algorithm>
#include "Game.h"
#include "GBMaps.h"
#include "GameObservers.h"
using namespace std;

int main() {
    Game* game = new Game();
    GameObserver* observer = new GameObserver(game);
    system("pause");
    game->run();
    delete game;
    game = NULL;
    system("pause");
}