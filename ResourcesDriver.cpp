#include "ResourcesDriver.h"

using namespace std;

int main() {
    Deck* d = new Deck();
    map<Type, string> enumValues = {{Type::Wheat, "Wheat"}, {Type::Stone, "Stone"}, {Type::Timber, "Timber"}, {Type::Sheep, "Sheep"}};
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

    Hand* hand = new Hand();
    Hand hand2 = *hand;
    hand2.exchange(9, 2, 3, 4);

    cout << "hi3" << endl;
    cout << *hand2.getSheepResourceMarker() << endl;
    cout << *hand2.getStoneResourceMarker() << endl;
    cout << *hand2.getTimberResourceMarker() << endl;
    cout << *hand2.getWheatResourceMarker() << endl;

    hand2.exchange(-3, -1, -1, 0);

    cout << "hi3" << endl;
    cout << *hand2.getSheepResourceMarker() << endl;
    cout << *hand2.getStoneResourceMarker() << endl;
    cout << *hand2.getTimberResourceMarker() << endl;
    cout << *hand2.getWheatResourceMarker() << endl;
};
