#include <iostream>
#include <vector>
#include "Resources.h"
#include "ResourcesDriver.h"

using namespace std;

int main() {
    Deck* d = new Deck();
    Building* building = d->drawBuilding();
    Building building2 = *building;
    int cost = *building2.getCost();
    cout << "hi" << endl;
    cout << building2.getType() << endl;
    cout << building2.getActualCost() << endl;
    cout << cost << endl;
    cout << endl;
    // d.buildingDeck->size();
};
