#include <iostream>
#include <vector>
#include "Resources.h"
#include "ResourcesDriver.h"

#define stringify( name ) # name


using namespace std;

int main() {
    Deck* d = new Deck();
    map<Type, string> enumValues = {{Type::Wheat, "wheat"}, {Type::Stone, "stone"}, {Type::Timber, "timber"}, {Type::Sheep, "sheep"}};
    Building* building = d->drawBuilding();
    Building building2 = *building;
    
    cout << "hi" << endl;
    cout << enumValues[*building2.getType()] << endl;
    cout << *building2.getActualCost() << endl;
    cout << *building2.getCost() << endl;
    cout << endl;

    HarvestTile* harvestTile = d->drawHarvestTile();
    HarvestTile harvestTile2 = *harvestTile;

    cout << "hi2" << endl;
    cout << enumValues[*harvestTile2.getBottomLeftNode()] << endl;
    cout << enumValues[*harvestTile2.getTopLeftNode()] << endl;
    cout << enumValues[*harvestTile2.getTopRightNode()] << endl;
    cout << enumValues[*harvestTile2.getBottomRightNode()] << endl;
    cout << endl;

    vector<Building*> b = *d->getBuildingDeck();
    vector<HarvestTile*> h = *d->getHarvestTileDeck();
    cout << b.size() << endl;
    cout << h.size() << endl;
};
