#include <iostream>
#include <vector>
#include "Resources.h"
#include "ResourcesDriver.h"

using namespace std;

int main() {
    Deck d;
    Building* building = d.drawBuilding();
    Building building2 = *building;
    cout << "hi";
    cout << building2.getType();
    cout << building2.getActualCost();
    cout << building2.getCost();
    cout << endl;

};
