#include <iostream>
#include <algorithm>
#include "Game.h"
#include "GBMaps.h"
using namespace std;

int main() {
    Game* game = new Game();

    system("pause");
    game->run();
    delete game;
    game = NULL;
    system("pause");
}