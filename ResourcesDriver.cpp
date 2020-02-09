#include <iostream>
#include "Score.h"
#include "Resources.cpp"

int main() {
    Deck* deck = new Deck();
    GBMaps* gbMap = new GBMaps(2);
    ResourceCounter* resourceCounter = new ResourceCounter(gbMap);
    Hand* hand = new Hand(deck, resourceCounter);

    cout << "========== TEST ==========" << endl;
    cout << "Enter the following coordinates: (1, 3)" << endl;
    cout << "Expected sheep resources gained at (1, 3): 1" << endl;
    Type* sheep = new Type{Type::Sheep};
    gbMap->getSquare(1, 3)->getBottomLeft()->setType(sheep);
    hand->exchange();
    cout << "Actual sheep resources gained at (1, 3): " << *hand->getSheepResourceMarker();
}
